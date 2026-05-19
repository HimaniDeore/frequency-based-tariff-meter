# frequency-based-tariff-meter
Smart Energy Meter using AT89S52 and PZEM-004T with Frequency-Based Dynamic Tariff Calculation
# Frequency Based Tariff Meter

A smart energy monitoring and dynamic tariff calculation system developed using the AT89S52 microcontroller and the PZEM-004T energy monitoring module. The system measures voltage, current, frequency, and energy consumption in real time and calculates electricity charges based on grid frequency.

The project was developed using Embedded C in Keil μVision and demonstrates UART communication, Modbus RTU protocol handling, LCD interfacing, and custom PCB design for embedded energy monitoring applications.

## Overview

With increasing electricity demand and the need for efficient power management, smart metering systems are becoming essential. Traditional energy meters use fixed pricing, whereas this project introduces a frequency-based tariff mechanism where the electricity rate changes according to the measured grid frequency.

The system continuously acquires electrical parameters from the PZEM-004T module through UART communication using the Modbus RTU protocol. The AT89S52 processes the received data, calculates units consumed and tariff amount, and displays the information on a 16×2 LCD.

The project combines embedded programming, serial communication, LCD interfacing, and PCB implementation into a compact real-time monitoring system.

## Objectives

- To design a smart frequency-based tariff meter using AT89S52
- To measure voltage, current, frequency, and energy in real time
- To interface the PZEM-004T module using UART and Modbus RTU
- To display electrical parameters on a 16×2 LCD
- To calculate tariff dynamically based on frequency
- To implement embedded firmware using Embedded C
- To design and implement a custom PCB for the system

## Features

- Real-time voltage monitoring
- Real-time current monitoring
- Frequency measurement
- Energy consumption monitoring
- Dynamic tariff calculation
- UART communication with PZEM-004T
- Modbus RTU frame handling
- 16×2 LCD display in 4-bit mode
- LED indication for data reception
- Custom PCB implementation
- Embedded C firmware using Keil

## Hardware Components

| Component | Description |
|---|---|
| AT89S52 | 8-bit 8051-based microcontroller |
| PZEM-004T v3.0 | Energy monitoring module |
| 16×2 LCD | Character LCD display |
| 11.0592 MHz Crystal | Clock source for accurate UART timing |
| Capacitors | Oscillator and power filtering |
| Potentiometer | LCD contrast adjustment |
| LED | Data reception indication |
| Arduino UNO | Used as ISP programmer |
| PCB | Custom-designed hardware board |

## Software Used

- Embedded C
- Keil μVision 5
- Arduino IDE
- AVRDUDE
- EasyEDA

## Working Principle

The AT89S52 microcontroller communicates with the PZEM-004T module through UART using the Modbus RTU protocol.

The firmware sends a Modbus request frame to the module requesting electrical parameters such as:
- Voltage
- Current
- Power
- Energy
- Frequency

The PZEM-004T returns the measured values in a serial data frame. The microcontroller extracts the required register values and converts them into meaningful electrical parameters.

The processed values are displayed on the 16×2 LCD.

The LCD displays:
- Voltage
- Current
- Frequency
- Units consumed
- Calculated tariff amount

An LED connected to Port P1.0 indicates successful data reception.

If communication fails or data is not received within the timeout period, the LCD displays:
"No Data Received"

## LCD Display Format

### Line 1
Voltage, Current, and Frequency

Example:
```txt
V:226.8 C:0.72 F:51
```

### Line 2
Units consumed and amount

Example:
```txt
U:005 Rs:025
```

## UART and Modbus Communication

The communication between the AT89S52 and PZEM-004T uses:
- UART serial communication
- 9600 baud rate
- Modbus RTU protocol

The Modbus request frame used in the code:

```c
unsigned char modbus_request[] = {
0x01, 0x04, 0x00, 0x00,
0x00, 0x0A, 0x70, 0x0D
};
```

The response data is parsed to extract:
- Voltage
- Current
- Power
- Energy
- Frequency

## Hardware Connections

### LCD Connections

| LCD Pin | AT89S52 Pin |
|---|---|
| RS | P2.0 |
| RW | P2.1 |
| EN | P2.2 |
| D4 | P2.4 |
| D5 | P2.5 |
| D6 | P2.6 |
| D7 | P2.7 |

### PZEM-004T Connections

| PZEM Pin | AT89S52 Pin |
|---|---|
| TX | P3.0 (RXD) |
| RX | P3.1 (TXD) |
| VCC | 5V |
| GND | GND |

### LED Connection

| Component | Pin |
|---|---|
| LED | P1.0 |

### Crystal Oscillator

| Component | Connection |
|---|---|
| 11.0592 MHz Crystal | XTAL1 and XTAL2 |
| Capacitors | Connected to GND |

## PCB Design

A custom PCB was designed for compact implementation of the project. The PCB integrates:
- AT89S52 microcontroller
- LCD interface
- Crystal oscillator circuit
- UART communication lines
- Power supply section
- ISP programming header

The PCB layout and schematic were designed using EasyEDA.

## Results

The system successfully measured and displayed:
- Voltage
- Current
- Frequency
- Energy consumption
- Calculated tariff amount

The LCD updated continuously with stable readings.

The LED indication confirmed successful communication with the PZEM-004T module.

The PCB implementation demonstrated compact and reliable hardware integration.

## Applications

- Smart energy metering
- Dynamic tariff monitoring
- Embedded systems learning
- Electrical parameter monitoring
- IoT and smart grid research
- Energy management systems

## Future Scope

- GSM or IoT-based monitoring
- Cloud data logging
- Mobile application integration
- Power quality analysis
- Remote energy monitoring
- Relay-based load control

## Conclusion

This project demonstrates the implementation of a frequency-based tariff meter using the AT89S52 microcontroller and PZEM-004T energy monitoring module. The system successfully performs real-time energy monitoring, UART communication, Modbus RTU data handling, LCD interfacing, and dynamic tariff calculation.

The project combines embedded programming and hardware implementation into a practical smart metering solution suitable for educational and research applications.

## Author

Himani Deore  
Electronics and Telecommunication Engineering
```
