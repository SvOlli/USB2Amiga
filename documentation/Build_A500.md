Build Configuration For Amiga 500
=================================

You can use the precompiled file `hex/USB2Amiga.A500.hex` to program the
Arduino pro mini 328p 3.3V.


Pins On Arduino
---------------

Pin | Signal    | Note
----|-----------|------------------------------
 2  | KBCLK     |
 3  | KBDAT     | may not be changed
 4  | KBRESET   |
 5  | DB9 Pin 1 | Y2 mouse signal
 6  | DB9 Pin 2 | X1 mouse signal
 7  | DB9 Pin 3 | Y1 mouse signal
 8  | DB9 Pin 4 | X2 mouse signal
A0  | DB9 Pin 6 | left mouse button
A1  | DB9 Pin 9 | right mouse button
A2  | DB9 Pin 5 | optional middle mouse button
GND | DB9 Pin 8 | mouse ground


[(Is the mentioned level shifter necessary?)](LevelShifter.md)

Pull these signals through a level shifter with LV# on the Arduino side and
HV# on the Amiga side. Note that you need at least 9 signals to get keyboard
and mouse working. Since I've seen a level shifter with more than 8 bits so
far, you will need two.

Connect all GNDs together: the GND of the keyboard connector, pin 8 of the
DB9 mouse connector, the Arduino pro mini and both sides of the level shifter.
There are level shifter that only have one GND and an extra connector called
"OE". According to
[this discussion](https://forum.arduino.cc/index.php?topic=406261.0)
this needs to be connected to +5V using a 1k Ohm pull-up resistor. +5V needs
to be connected to HV of the level shifter, RAW of the Arduino pro mini and
the +5V pin of the keyboard connector. The +5V of the DB9 mouse connector
can be skipped, since we are getting power from the keyboard connector
already.

The DB9 pins are described above, the pins of the keyboard connector differ
from model to model.


A500
----

Pin | Function
----|-----------
 1  | KBCLK
 2  | KBDAT
 3  | KBRESET
 4  | +5V
 5  | n/c / key
 6  | GND
 7  | STATUS
 8  | INUSE

