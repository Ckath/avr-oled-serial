![demo](demo.png)
---
simple avr program exposing some oled library functions over a serial connection, uses a patched version of the [oled-display](https://github.com/Sylaina/oled-display)`fa446f6` library for controlling the display. currently only tested on an ssd1306 128x32 display and arduino uno, but it should be straight forward to make it work on other devices.

## usage
open a serial connection baudrate `115200`,\
use the commandset:

cmd    | action
---    | ---
Wn str | write *str* to row *n*
C      | clear screen

## todo
- test support for 128x64 display
- add more commands
- strip down/extend oled library
