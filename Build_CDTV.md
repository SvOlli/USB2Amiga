Build Configuration For CDTV
============================

You can use the precompiled file `hex/USB2Amiga.CDTV.hex` to program the
Arduino pro mini 328p 3.3V.

Pins On Arduino
---------------

Pin | Signal | Note
----|--------|-------------------
 2  | KBCLK  | 
 3  | KBDAT  | may not be changed
 6  | PRDT   | 

Pull these signals through a level shifter with LV# on Arduino side and HV#
on CDTV side. The pins 2, 3 and 6 match the layout of the typical 4-bit
level shifters, where the pins in the center are used for GND and refence
voltage.

Also connect +5V from both ports to RAW on the Arduino Pro Mini and HV on
the level shifter. LV of the level shifter is connected to 3.3V (VCC) on
the Arduino.

GND should be connected to both CDTV ports, GND on both sides of the level
shifter and GND on the Arduino. This way the converter works also when only
one port is connected for that port.

Pins On CDTV
------------
![CDTV connectors](images/cdtv_kb_mouse.png)
