Arduino Pro Mini Pins Usage
===========================

This file will be removed, once the build instructions for all different
versions are completed.

Note: pins 18-21 (A4-A7) are not on the sides, but inside of the board.

Pin | Function | Amiga
----|----------|--------------------------------------------------
  0 | PD0/TX   | serial interface for debug (*)
  1 | PD1/RX   | serial interface for debug (*)
  2 | PD2/INT0 | KBCLK (*)
  3 | PD3/INT1 | KBDAT (*)
  4 | PD4      | mouse DB9 pin 1: Y2 (*)
  5 | PD5      | mouse DB9 pin 2: X1 (*)
  6 | PD6      | mouse DB9 pin 3: Y1 (*) / CDTV-PRDT (*)
  7 | PD7      | mouse DB9 pin 4: X2 (*)
  8 | PB0      | mouse DB9 pin 6: LB (*)
  9 | PB1/INTR | USB host shield (*)
 10 | PB2/SS   | USB host shield (*)
 11 | PB3/MOSI | USB host shield (*)
 12 | PB4/MISO | USB host shield (*)
 13 | PB5/SCK  | USB host shield (*) / LED
 14 | PC0/A0   | input joystick DB9 (*) / mouse DB9 pin 9: RB (*)
 15 | PC1/A1   | input joystick DB9 (+) / mouse DB9 pin 5: MB (+)
 16 | PC2/A2   | input joystick DB9 (+) / A500 reset (+)
 17 | PC3/A3   | input joystick DB9 (+)
 18 | PC4/A4   | input joystick DB9 (+)
 19 | PC5/A5   | input joystick DB9 (+)
 20 | ADC6/A6  |
 21 | ADC7/A7  | 

- (+) = currently implemented
- (*) = currently implemented and tested

Note: not all combinations are available in all versions
