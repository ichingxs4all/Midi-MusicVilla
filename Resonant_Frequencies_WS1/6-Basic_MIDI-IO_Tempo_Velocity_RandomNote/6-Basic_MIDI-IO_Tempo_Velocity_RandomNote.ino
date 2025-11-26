// Simple example of playing a random MIDI note on channel 1 in a tempo based on the level of a potentiometer ( sensor) connected to A0
// The velocity or loudness is controlled by a lightsensor connected to A1
// by Michel Gutlich for the Resonant Frequencies workshop #1

#define LED_BUILTIN 3 // A led is attached to pin 3 to have some visual indication of what is happening
#define SENSORPIN A0 //A potentiometer is connected to A0
#define VELOCITYPIN A1 //A lightsensor is connected to A1

// We are goin to use the FortySevenEffects MIDI library. Make sure it downloaded and installed through the Library Manager
//https://github.com/FortySevenEffects/arduino_midi_library
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE(); //Create a standard instance of a hardware Serial Port MIDI device

int tempo = 500; // Declare the variable 'tempo' and give it the initial value of 500;

int channel = 1; //The MIDI channel we are going to send messages to. Make this the channel number your synthesizer is set on. Channel numbers are between 1 and 16

int note = 42; //The note number we are going send. Note numbers are between 0 and 127

int velocity = 126; //The velocity ( volume) of the note we are going to send. Velocty value are between 0 and 127 

int velScale = 4; // scale factor for the velocity readings

bool debug = false; //Set this to false to turn off debugging to the USB serial port

void setup()
{
    if(debug)Serial.begin(115200); //Setup the USB serial port for debugging

    pinMode(LED_BUILTIN, OUTPUT);    //Set the pin where the led is attached to as an output
    MIDI.begin(MIDI_CHANNEL_OMNI);   // Launch MIDI and listen on all channels
    analogReference(EXTERNAL); //Set the analog reference to external so we can use 3.3 volts as a reference. A wire must be connected from the ARef pin to 3.3V
}

void loop()
{
    MIDI.read();            // Listen for incomming MIDI messages. It's a good thing to always implement this function in your own code
    
    tempo = analogRead(SENSORPIN); // Read analog port A0 and put the value in the parameter tempo. The value will be between 0 and 1023

    velocity = analogRead(VELOCITYPIN)/velScale; // Read analog port A1 and put the value in the parameter velocity. The value will be between 0 and 1023 zo we have to divide it by a scale factor to be in range

    note = random(60,100); //Choose a random note number between 60 and 100
    
    if(debug) Serial.println(velocity); //Send the value to the USB Serial port

    digitalWrite(LED_BUILTIN, HIGH); //Turn the led on
    
    MIDI.sendNoteOn(note, velocity, channel);    // Send the note with a velocity on a channel
    
    delay(tempo/2);		    // Wait for half time the tempo ( in mSec)
    
    MIDI.sendNoteOff(note, 0, channel);  // Stop the note
    
    digitalWrite(LED_BUILTIN, LOW); //Turn off the led
    
    delay(tempo/2);	        // Wait for half time the tempo ( in mSec)
    
}

//Experiments:
//Make the range of the random notes controlable by the potmeter
//Play two notes in a random interval
//Make the gatelength variabel with the potmeter

