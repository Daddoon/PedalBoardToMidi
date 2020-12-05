#include <Bounce2\Bounce2.h>

void PinOutput(int pinNb, int pinValue)
{
	Serial5.print("Pin: ");
	Serial5.print(pinNb);
	Serial5.print(", Value: ");
	Serial5.println(pinValue);
}

struct KeyNote
{
	int pin; //pin number on Teensy card
	int value; //Note value in Midi
	Bounce button; //Bounce instanciated button
};

const int channel = 1;
const int debounceTime = 5;
const int noteOn = 99;
const int noteOff = 0;
const int nbKeys = 32;

KeyNote keys[] = {
	{ 0, 60 }, //Key 1, Note value => 60 (C4)
	{ 1, 61 }, //Key 2
	{ 2, 62 }, //Key 3
	{ 3, 63 }, //Key 4
	{ 4, 64 }, //Key 5
	{ 5, 65 }, //Key 6
	{ 6, 66 }, //Key 7
	{ 7, 67 }, //Key 8
	{ 8, 68 }, //Key 9
	{ 9, 69 }, //Key 10
	{ 10, 70 }, //Key 11
	{ 11, 71 }, //Key 12
	{ 12, 72 }, //Key 13 
	{ 32, 73 }, //Key 14 //NOTE: Using Pin 32 instead of Pin 13, because LED is interupting normal signals
	{ 14, 74 }, //Key 15
	{ 15, 75 }, //Key 16
	{ 16, 76 }, //Key 17
	{ 17, 77 }, //Key 18
	{ 18, 78 }, //Key 19
	{ 19, 79 }, //Key 20
	{ 20, 80 }, //Key 21
	{ 21, 81 }, //Key 22
	{ 22, 82 }, //Key 23
	{ 23, 83 }, //Key 24
	{ 24, 84 }, //Key 25
	{ 25, 85 }, //Key 26
	{ 26, 86 }, //Key 27
	{ 27, 87 }, //Key 28
	{ 28, 88 }, //Key 29
	{ 29, 89 }, //Key 30
	{ 30, 90 }, //Key 31
	{ 31, 91 }  //Key 32
};

void BounceSetup()
{
	int i = 0;
	while (i < nbKeys)
	{
		keys[i].button = Bounce(keys[i].pin, debounceTime);
		i++;
	}
}

void PullUpSetup()
{
	int i = 0;
	while (i < nbKeys)
	{
		pinMode(keys[i].pin, INPUT_PULLUP);
		i++;
	}
}

void setup()
{
	/*Serial5.begin(9600);*/

	BounceSetup();
	PullUpSetup();
}

void UpdateKeys()
{
	int i = 0;
	while (i < nbKeys)
	{
		keys[i].button.update();
		i++;
	}
}

void SendNoteOn()
{
	int i = 0;
	while (i < nbKeys)
	{
		// Note On messages when each button is pressed
		if (keys[i].button.fallingEdge()) {
			usbMIDI.sendNoteOn(keys[i].value, noteOn, channel);
			
			//Debug only
			/*PinOutput(keys[i].pin, keys[i].value);*/
		}

		i++;
	}
}

void SendNoteOff()
{
	int i = 0;
	while (i < nbKeys)
	{
		// Note Off messages when each button is released
		if (keys[i].button.risingEdge()) {
			usbMIDI.sendNoteOn(keys[i].value, noteOff, channel);
		}

		i++;
	}
}

void DiscardAllInputs()
{
	// MIDI Controllers should discard incoming MIDI messages.
	while (usbMIDI.read()) {
	}
}

void loop()
{
	UpdateKeys();

	SendNoteOn();
	SendNoteOff();

	DiscardAllInputs();
}
