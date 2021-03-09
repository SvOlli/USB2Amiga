Arduino Pro Mini Pins Usage
===========================

The tables try to resemble the layout of the board with the programming
pins on top.


CDTV
----
|       Function | Pin | | Pin | Function              |
|---------------:|:----|-|----:|:----------------------|
|      Serial TX |   0 | | Vin | Power (+5V)           |
|      Serial RX |   1 | | GND | Ground                |
| Reset (unused) | RST | | RST | Reset (unused)        |
|         Ground | GND | | VCC | +3.3V (not connected) |
|         KB_CLK |   2 | | A3  | joystick input right  |
|         KB_DAT |   3 | | A2  | joystick input left   |
|      (FF next) |   4 | | A1  | joystick input down   |
|      (FF prev) |   5 | | A0  | joystick input up     |
|      CDTV_PRDT |   6 | | 13  | USB host SCK          |
|                |   7 | | 12  | USB host MISO         |
|                |   8 | | 11  | USB host MOSI         |
|  USB host INTR |   9 | | 10  | USB host SS           |

Pins inside the board:

| Pin | Function                |
|----:|:------------------------|
|  A4 | joystick input button A |
|  A5 | joystick input button B |

Note: pins A4/A5 will be moved to 7/8 soon.


DB9 ("Big Box" Amigas)
----------------------
|         Function | Pin | | Pin | Function              |
|-----------------:|:----|-|----:|:----------------------|
|        Serial TX |   0 | | Vin | Power (+5V)           |
|        Serial RX |   1 | | GND | Ground                |
|   Reset (unused) | RST | | RST | Reset (unused)        |
|           Ground | GND | | VCC | +3.3V (not connected) |
|           KB_CLK |   2 | | A3  | (FF prev)             |
|           KB_DAT |   3 | | A2  | (FF next)             |
| Mouse Y2 (DB9-1) |   4 | | A1  | Mouse MB (DB9-5)      |
| Mouse X1 (DB9-2) |   5 | | A0  | Mouse RB (DB9-9)      |
| Mouse Y1 (DB9-3) |   6 | | 13  | USB host SCK          |
| Mouse X2 (DB9-4) |   7 | | 12  | USB host MISO         |
| Mouse LB (DB9-6) |   8 | | 11  | USB host MOSI         |
|    USB host INTR |   9 | | 10  | USB host SS           |


Amiga 500
---------
|         Function | Pin | | Pin | Function              |
|-----------------:|:----|-|----:|:----------------------|
|        Serial TX |   0 | | Vin | Power (+5V)           |
|        Serial RX |   1 | | GND | Ground                |
|   Reset (unused) | RST | | RST | Reset (unused)        |
|           Ground | GND | | VCC | +3.3V (not connected) |
|           KB_CLK |   2 | | A3  |                       |
|           KB_DAT |   3 | | A2  | Mouse MB (DB9-5)      |
|         KB_RESET |   4 | | A1  | Mouse RB (DB9-9)      |
| Mouse Y2 (DB9-1) |   5 | | A0  | Mouse LB (DB9-6)      |
| Mouse X1 (DB9-2) |   6 | | 13  | USB host SCK          |
| Mouse Y1 (DB9-3) |   7 | | 12  | USB host MISO         |
| Mouse X2 (DB9-4) |   8 | | 11  | USB host MOSI         |
|    USB host INTR |   9 | | 10  | USB host SS           |

Pins inside the board:

| Pin | Function  |
|----:|:----------|
|  A4 | (FF next) |
|  A5 | (FF prev) |
