// Simple example of playing a fixed MIDI note on channel 1 in a tempo based on the level of a potentiometer ( sensor) connected to A0;
//The velocity or loudness of the note is based on the value of lightsensor connected to A1
//by Michel Gutlich for the Resonant Frequencies workshop #2

#define LED_BUILTIN 3 // A led is attached to pin 3 to have some visual indication of what is happening
#define SENSORPIN A0 //A potentiometer is connected to A0
#define VELOCITYPIN A1 //A lightsensor is connected to A1

// We are goin to use the FortySevenEffects MIDI library. Make sure it downloaded and installed through the Library Manager
//https://github.com/FortySevenEffects/arduino_midi_library
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE(); //Create a standard instance of a hardware Serial Port MIDI device

int tempo = 500; // Declare the variable 'tempo' and give it the initial value of 500 mSec;

int channel = 1; //The MIDI channel we are going to send messages to. Make this the channel number your synthesizer is set on. ( range = 1 - 16 )

int note = 42; //The note number we are going send ( range = 0 - 127 )

int velocity = 100; //The initial velocity ( volume) of the note we are going to send ( range = 0 - 127 )

int ccNo = 16; //The control change number to use  

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);    //Set the pin where the led is attached to as an output
    MIDI.begin(MIDI_CHANNEL_OMNI);   // Launch MIDI and listen on all channels
    analogReference(EXTERNAL); //Set the analog reference to external so we can use 3.3 volts as a reference. A wire must be connected from the ARef pin to 3.3V
}

void loop()
{
    MIDI.read();            // Listen for incomming MIDI messages. It's a good thing to always implement this function in your own code
    
    tempo = analogRead(SENSORPIN); // Read analog port A0 and put the value in the parameter tempo. The value will be between 0 and 1023

    velocity = analogRead(VELOCITYPIN)/10 ; // Read analog port A1 and put the value in the parameter velocity. The value will be between 0 and 1023 zo we have to divide it by 10 to be in range
   
    digitalWrite(LED_BUILTIN, HIGH); //Turn the led on
    
    MIDI.sendNoteOn(note, velocity, channel);    // Send the note with a velocity on a channel
    
    delay(tempo/2);		    // Wait for half time the tempo ( in mSec)
    
    MIDI.sendNoteOff(note, 0, channel);  // Stop the note
    
    digitalWrite(LED_BUILTIN, LOW); //Turn off the led
    
    delay(tempo/2);	        // Wait for half time the tempo ( in mSec)
    
}

//Experiments:
//Make the note a random one 
//Make the note a value defined by the light sensor
//Make the tempo a value defined by the light sensor
//
// Send a control change according to the lightsensor
// Use MIDI.sendControlChange(ccNo, velocity, channel);
