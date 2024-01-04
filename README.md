# About

Firmware for STM32F030 controller used in a relay module to control up to 14 relay outputs.

# Description

The relay controller was designed to communicate over serial port and utilises a simple byte-protocol:

* 0d220 - heartbeat message, if not present for longer then 3 minutes all relay outputs will be turned off
* 0d100 - turn on the first relay
* 0d105 - turn off the first relay
* 0d110 - turn on the second relay
* 0d115 - turn off the second relay
* etc...

In response the device returns byte it received.

# Building

To build the code [IAR IDE/Compiler](https://www.iar.com/st) for ARM is required.