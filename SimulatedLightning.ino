/*************************************************

SIMULATED LIGHTNING using an RGB LED
Sketch by: Paul Riggs

This sketch uses randomized variables to create realistic lightning effects
as a result, there's no repetion of similar effects... each sequence is unique.

This sketch can accomodate either Common CATHODE or ANODE RGB LEDs
However setup is slightly different dedending on which is used

For common CATHODE:
    The cathode (long leg) must be connected to GND...
	    and connect each of the other pins via a 220 ohm resistor as follows:
	    RED - to pin 11~, GREEN - pin 10~, and BLUE - to pin 9~
	Also set the first line of this set to "true"
	    "bol common_cathode = true"
		
For common ANODE:
    The anode (long leg) must be connected to 5V...
        and connect each of the other pins via a 220 ohm resistor as follows:
	    RED - to pin 11~, GREEN - pin 10~, and BLUE - to pin 9~
	Also set the first line of this sketch to "false"
	    "boolean commonCathode = false"

**************************************************/

	// Set the type of LED used (common CATHODE or common ANODE)
		boolean commonCathode = true;  // true for common CATHODE - false for common ANODE

	// Declare the limits for variables

		int flashesMin = 2;  // Number of quick PURPLE flashes before bright WHITE burst
		int flashesMax = 6;

		int flashspeedMin = 20;  // Timing of quick PURPLE flashes in msec (lower is FASTER)
		int flashspeedMax = 80;

		int brightnessMin = 128;  // Brightness level of bright WHITE burst (0-255) (higher is BRIGHTER)
		int brightnessMax = 255;

		int durationMin = 100;  // length of bright WHITE burst in msec (higher is LONGER)
		int durationMax = 500;

		int fadeChance = 50;  // likelyhood of dull PURPLE fade vs complete DARK between events (percentage 0-100) (100 = ALWAYS & 0 = NEVER)

		int fadeWaitMin = 500;  // length of time between events in msec (higher is LONGER)
		int fadeWaitMax = 4000;

	// Declare the pins and set their assigned color
		int redPin = 11;
		int greenPin = 10;
		int bluePin = 9;
		//  Don't forget... long leg must be connected to GND (Cathode) or 5V (Anode)

void setup()
{
	// Set the pins to outputs
		pinMode(redPin, OUTPUT);
		pinMode(greenPin, OUTPUT);
		pinMode(bluePin, OUTPUT);
}

void loop()
{
	// Establishes variable values for each event
		int flashes = random(flashesMin,flashesMax);
		int flashspeed = random(flashspeedMin,flashspeedMax);
		int brightness = random(brightnessMin,brightnessMax);
		int flashBrightness = brightness/3;
		int burstBrightness = brightness;
		int duration = random(durationMin,durationMax);
		int fadeBrightness = brightness/8;
		int fadeWait = random(fadeWaitMin,fadeWaitMax);
		int fadeRoll = random(0,100);
		if (fadeRoll > fadeChance) fadeBrightness = 0; //determines if wait will be faded or DARK
  
		for (int i=0; i<flashes; i++)
		{
			setColor(flashBrightness/2,0,flashBrightness); //dim PURPLE flashes
			delay(flashspeed);
			setColor(0,0,0);  //clears color from LED
			delay(flashspeed);
		}

		setColor(burstBrightness,burstBrightness,burstBrightness);  //bright WHITE burst
		delay(duration);
		setColor(fadeBrightness,0,fadeBrightness);  //sets fade color until next event
		delay(fadeWait);  
}
  
void setColor(int red, int green, int blue)
{
	if (commonCathode == true)
	{
		analogWrite(redPin, red);
		analogWrite(greenPin, green);
		analogWrite(bluePin, blue);
	}
	else
	{
		analogWrite(redPin, 255-red);
		analogWrite(greenPin, 255-green);
		analogWrite(bluePin, 255-blue);
	}
}
