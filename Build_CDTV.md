Build Configuration For CDTV
============================

Pins On Arduino
---------------

Pin | Signal | Note
----|--------|-------------------
 2  | KBCLK  | 
 3  | KBDAT  | may not be changed
 6  | PRDT   | 

Pull these signals through a level shifter, LV on Arduino side, HV on CDTV
side. Connect +5V from both ports to RAW on the Arduino Pro Mini and HV on
the level shifter. LV of the level shifter is connected to 3.3V (VCC) on the
Arduino. GND should be connected to both CDTV ports, GND on both sides of
the level shifter and GND on the Arduino. This way the converter works also
when only one port is connected for that port.

Pins On CDTV
------------
![CDTV connectors](images/cdtv_kb_mouse.png)
