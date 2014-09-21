arduino-cv-voltage-adjust-5v
============================

An arduino program that uses an MCP4725 to generate an
adjustable control voltage from 0 to 5 volts.

In the Arduino IDE, go to the Sketch menu and choose Import Library...
-> Add Library, then choose the Adafruit_MCP4725 folder.

This program uses two Bourns PEC12-4225F-N0024 rotary encoders.
Hook both C pins to ground, the A and B pins of
one to digital inputs 2 and 3, and the A and B pins of the other
to digital inputs 4 and 5. To change the direction the pot is
turned to increase the voltage, swap the
A and B pins for that pot.

One of the pots is fine control, one of them is coarse control.

See this adafruit tutorial to hook up the MCP4725:

https://learn.adafruit.com/mcp4725-12-bit-dac-tutorial/wiring

Donovan Preston
September 21, 2014
