ATtiny85 KITT with 20 Charlieplexed LEDs
========================================

ATtiny85 Larson scanner effect, using Arduino core 

This project is an adaption of the ATTiny85 snowflakes, to create my take on the Larson scanner effect used in Knight Rider's KITT.

The animation has a bright LED in the middle, with 3 either side with diminishing brightness.

Operation
---------
Animation operates while powered on.

ATtiny85 pin assignments 
------------------------
(legs numbered 1..8 counterclockwise from leg marked with dot)

1. Reset, no connection
2. D3 GREEN channel
3. D4 ORANGE channel
4. GND
5. D0 WHITE channel
6. D1 BLUE channel
7. D2 YELLOW channel
8. +5V

Code
----
Written using the Arduino IDE and Arduino-Tiny cores (http://code.google.com/p/arduino-tiny/); the target to select is the ATtiny85 @ 8MHz (internal oscillator, BOD disabled).  Look up how to program the ATtiny using Arduino, and programming it using Arduino as an IDE.  

Tested installation
-------------------
For simplicity of wiring on breadboard, and for matching to function in the code, this was wired using a colour code.  A breadboard circuit diagram created in Fritzing is included to explain how two of those channels are wired.

I started the breadboard with a row of 20 LEDs, each with the flat side to the right.  For a more permanent installation, rotating the LEDs so the flat side is top or bottom would allow for ease of wiring.  Each group of 4 LEDs shares a direct connection to one pin directly without a resistor, with the 4 anodes (+, or the long LED leg) linked.  Then the other legs are connected via a current limiting resistor to the other colours in the sequence green, orange, white, blue, yellow (always in this order, but omitting of course the colour that the anodes are).

So the green group has green to the anodes, then the cathodes in left to right sequence are orange, white, blue & yellow.  The orange group has orange to the anodes, with green, white, blue & yellow to the cathodes left to right.  White group's cathodes are sequenced green, orange, blue & yellow; the blue group's cathodes go green, orange, white & yellow; and the yellow group's cathodes go green, orange, white & blue.

BoM as tested:

	1x ATtiny85-20PU & 8DIP socket
	20x 5mm red LED
	5x 180 Ohm resistors (current limiting, for LEDs)
	1x LM7805 voltage regulator
	2x 0.1uF ceramic capacitor (power regulator decoupling)
	1x 47uF electrolytic capacitor & 1x 470uF electrolytic capacitor (power regulator decoupling)
	1x 1N4001 diode (reverse polarity protection on power)
	1x 9V battery holder
	1x 1P1T switch (power switch)
	lots of interconnecting wire!

Be sure to choose current limiting resistors to suit the particular LED you select.
  
Enjoy : ) 
