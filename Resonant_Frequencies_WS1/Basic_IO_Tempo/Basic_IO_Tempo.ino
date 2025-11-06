
// Simple example of playing a fixed MIDI note in a tempo based on the level of a potentiometer ( sensor) connected to A0;
//by Michel Gutlich for the Resonant Frequencies workshop #1

#define LED_BUILTIN 3. // A led is attached to pin 3 to have some visual indication of what is happening
#define SENSORPIN A0

// We are goin to use the FortySevenEffects MIDI library. Make sure it downloaded and installed through the Library Manager
//https://github.com/FortySevenEffects/arduino_midi_library
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE(); //Create a standard instance of a hardware Serial Port MIDI device

int tempo = 500; // Declare the variable 'tempo' and give it the initial value of 1024;

int channel = 1; //The MIDI channel we are going to send messages to. Make this the channel number your synthesizer is set on.

int note = 42; //The note number we are going send

int velocity = 100; //The velocity ( volume) of the note we are going to send

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);    //Set the pin where the led is attached to as an output
    MIDI.begin(MIDI_CHANNEL_OMNI);   // Launch MIDI and listen on all channels
}

void loop()
{
    MIDI.read();            // Listen for incomming MIDI messages. It's a good thing to always implement this function in your own code
    
    tempo = analogRead(SENSORPIN); // Read analog port A0 and put the value in the parameter tempo. The value will be between 0 and 1023
    
    digitalWrite(LED_BUILTIN, HIGH); //Turn the led on
    
    MIDI.sendNoteOn(note, velocity, channel);    // Send the note with a velocity on a channel
    
    delay(tempo/2);		    // Wait for half time the tempo ( in mSec)
    
    MIDI.sendNoteOff(note, 0, channel);  // Stop the note
    
    digitalWrite(LED_BUILTIN, LOW); //Turn off the led
    
    delay(tempo/2);	        // Wait for half time the tempo ( in mSec)
    
}
