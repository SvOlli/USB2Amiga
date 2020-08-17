Thoughts About Using A Level Shifter
====================================

Due to the
[data sheet](http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)
of the ATmega 328p which states:

> Voltage on any pin except RESET with respect to ground: min=-0.5 max=Vcc+0.5

it should not be allowed to attach 5V to any data pin. But the Amiga uses 5V
for data signals. Other 3.3V microcontrollers sometimes state that they are
"5V tolerant", so that you can attach them to 5V input, but they will only
output 3.3V as a high signal. But the data sheet does not state this option.

But the ATmega 328p can be powered by either 3.3V or 5V. So I can't think of
any way using 5V as input while being powered by just 3.3V could not work or
break anything.

Another point is that the data is open collector. So a logical zero is stated
by setting that data pin to GND, and a logical one is stated by setting the
data pin to input, as the line is automatically pulled up.

So in my personal oppinion, even though it violates the specification of the
ATmega 328p, skipping the level shifter(s) should be okay. I have run a board
without any level shifter for a couple of days without any problems.

But that's just my oppinion...
