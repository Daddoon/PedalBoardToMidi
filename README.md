# PedalBoardToMidi
The source code of my 32 pedals 'GZ Pedalboard' device running on Teensy 3.5 / Arduino, built by myself for my Hauptwerk custom Organ.

## Tools and hardware used

- A Pedalboard taken from an old non-functionning analogic Organ
- [Teensy 3.5 - USB Development Board with Pins](https://www.pjrc.com/store/teensy35_pins.html) - I'm a developer, not an electronic nor soldering expert
- Breadboard - For testing and prototyping and also as my final device mount.
- Electronic testing wires (Female to Male)
- Some glue
- Visual Studio 2017 - At the time when the code was written.
- [VisualMicro](https://www.visualmicro.com/) - Arduino IDE for Visual Studio 

## Teensy 3.5 Card - Documentation

[<img src="./img/card8a_rev2.png?raw=true" align="center" width="632">]() 

[<img src="./img/card8b_rev2.png?raw=true" align="center" width="632">]()

## The Pedalboard type

Before anything else, it's important to mention and show the type of Pedalboard used, as there is many Pedalboard mecanism used through the time !
The one i found is working in two parts:

- The Pedalboard itself, that is only wood
- The Pedalboard analogical input mecanism: This part is behind the Pedalboard and is composed from 32 key switchs, that look like 32 rigid metal bands. When the user push a key on his Pedalboard, the rigid metal band bend and go in contact with two metal rods just placed behind.

The main idea on this kind of mecanism is that when the metal rods and the metal band are in contact, the electricity going through the wire can go to the ground, as one metal rod should be wired to the electronical system, and the other one to the ground, so current is going from whatever Volts value to 0 Volts !

So on this code implementation, we are just checking for everynote if we have voltage or not. If not, this mean that the key is actually pressed and that we should send the correct MIDI signal.

Here are two "old" photos from the Pedalboard. Not very clean, it was like some times before i construct the project myself, but you will get the idea of what the mecanism look like for this kind of project:

[<img src="./img/pedalboard.jpg?raw=true" align="center" width="632">]()
[<img src="./img/pedalboard-back.jpg?raw=true" align="center" width="632">]()
[<img src="./img/pedal-wire-front.jpg?raw=true" align="center" width="632">]() 
[<img src="./img/pedal-wire-back.jpg?raw=true" align="center" width="632">]() 


## How to connect the Pedalboard to the Teensy 3.5

