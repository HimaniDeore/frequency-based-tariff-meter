#include <reg52.h>
#include <string.h>
#include <stdio.h>

#define LCD P2
sbit RS = P2^0;
sbit RW = P2^1;
sbit EN = P2^2;
sbit LED = P1^0;

unsigned char data_received[25];
unsigned char modbus_request[] = {0x01, 0x04, 0x00, 0x00, 0x00, 0x0A, 0x70, 0x0D};  // Read 10 registers

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 1275; j++);
}

void lcd_cmd(unsigned char cmd) {
    LCD = (cmd & 0xF0); 
    RS = 0; RW = 0; EN = 1; delay_ms(2); EN = 0;
    
    LCD = ((cmd << 4) & 0xF0);
    RS = 0; RW = 0; EN = 1; delay_ms(2); EN = 0;
}

void lcd_data(unsigned char dat) {
    LCD = (dat & 0xF0); 
    RS = 1; RW = 0; EN = 1; delay_ms(2); EN = 0;
    
    LCD = ((dat << 4) & 0xF0);
    RS = 1; RW = 0; EN = 1; delay_ms(2); EN = 0;
}

void lcd_init() {
    lcd_cmd(0x02);  // 4-bit mode
    lcd_cmd(0x28);  // 2 line, 5x8 matrix
    lcd_cmd(0x0C);  // Display on, cursor off
    lcd_cmd(0x06);  // Increment cursor
    lcd_cmd(0x01);  // Clear display
}

void lcd_string(char *str) {
    while(*str) {
        lcd_data(*str++);
    }
}

void lcd_set_cursor(unsigned char row, unsigned char col) {
    unsigned char pos = (row == 1) ? 0x80 + col : 0xC0 + col;
    lcd_cmd(pos);
}

void uart_init() {
    TMOD = 0x20;
    TH1 = 0xFD;  // 9600 baud @ 11.0592MHz
    SCON = 0x50;
    TR1 = 1;
}

void uart_tx(unsigned char ch) {
    SBUF = ch;
    while(!TI);
    TI = 0;
}

void send_modbus_request() {
    unsigned char i;
    for(i = 0; i < sizeof(modbus_request); i++) {
        uart_tx(modbus_request[i]);
    }
}

unsigned int read_data(unsigned char high, unsigned char low) {
    return ((unsigned int)high << 8) | low;
}

void display_data() {
    unsigned int voltage_raw = read_data(data_received[3], data_received[4]);
    unsigned int current_raw = read_data(data_received[5], data_received[6]);
    unsigned int power_raw   = read_data(data_received[7], data_received[8]); // Not used directly
    unsigned int energy_raw  = read_data(data_received[9], data_received[10]);
    unsigned int freq_raw    = read_data(data_received[11], data_received[12]);

    float voltage = voltage_raw / 10.0;
    float current = current_raw / 100.0;
    float frequency = freq_raw / 10.0;
    float units = energy_raw / 1000.0;
    int amount = (int)(units * 5);

    char line1[17], line2[17];

    sprintf(line1, "V:%.1f C:%.2f F:%.1f", voltage, current, frequency);
    sprintf(line2, "U:%03d Rs:%03d", (int)units, amount);

    lcd_cmd(0x01);
    lcd_set_cursor(1, 0);
    lcd_string(line1);
    lcd_set_cursor(2, 0);
    lcd_string(line2);
}

bit receive_data() {
    unsigned char i;
    unsigned int timeout = 0;
    
    for(i = 0; i < 25; i++) {
        while(!RI) {
            if(++timeout > 50000) return 0;
        }
        data_received[i] = SBUF;
        RI = 0;
    }
    return 1;
}

void main() {
    lcd_init();
    uart_init();

    lcd_set_cursor(1, 2);
    lcd_string("Energy Meter");
    delay_ms(2000);
    lcd_cmd(0x01);

    while(1) {
        send_modbus_request();

        if(receive_data()) {
            LED = 1;
            display_data();
        } else {
            LED = 0;
            lcd_cmd(0x01);
            lcd_set_cursor(1, 0);
            lcd_string("No Data Received");
        }

        delay_ms(3000);
    }
}
