
// Simple example of playing a fixed MIDI note in a tempo based on the level of a potentiometer ( sensor);
//by Michel Gutlich for the Resonant Frequencies workshop #1

#define LED_BUILTIN 3. // A led is attached to pin 3 to have some visual indication of what is happening

// We are goin to use the FortySevenEffects MIDI library. Make sure it downloaded and installed through the Library Manager
//https://github.com/FortySevenEffects/arduino_midi_library
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE(); //Create a standard instance of a hardware Serial Port MIDI device

int tempo = 500; // Declare the variable 'tempo' and give it the initial value of 1024;

int channel = 14; //The MIDI channel we are going to send messages to. Make this the channel number your synthesizer is set on. Channel numbers are between 1 and 16

int note = 42; //The note number we are going send. Note numbers are between 0 and 127

int velocity = 100; //The velocity ( volume) of the note we are going to send. Velocty value are between 0 and 127 

int velScale = 4; // scale factor for the velocity readings

bool debug = true; //Set this to false to turn off debugging to the USB serial port

int numNotesInScale; //This will hold the number of notes in a scale 

int scale = 1 ; //This parameter will set the type of scale , 0 = chromatic, 1 = pentatatonic and 2 = blues scale

int playing; //This will hold a temporary value of the note  that is selected for playing after mapping it to a scale

void setup()
{
    if(debug) Serial.begin(115200); //Setup the USB serial port for debugging if the boolean 'debug' is true

    pinMode(LED_BUILTIN, OUTPUT);    //Set the pin where the led is attached to as an output
    MIDI.begin(MIDI_CHANNEL_OMNI);   // Launch MIDI and listen on all channels
}

void loop()
{
    MIDI.read();            // Listen for incomming MIDI messages. It's a good thing to always implement this function in your own code
    
    tempo = analogRead(A0); // Read analog port A0 and put the value in the parameter tempo. The value will be between 0 and 1023

    velocity = analogRead(A1)/velScale; // Read analog port A1 and put the value in the parameter velocity. The value will be between 0 and 1023 zo we have to divide it by a scale factor to be in range

    note = setScale(random(12), 2, 32); //Choose a random note number between 0 and 127, scale it and transpose it 
    
    if(debug) Serial.println(note); //Send the value to the USB Serial portfor debugging if the boolean 'debug' is true

    digitalWrite(LED_BUILTIN, HIGH); //Turn the led on
    
    MIDI.sendNoteOn(note, velocity, channel);    // Send the note with a velocity on a channel
    
    delay(tempo/2);		    // Wait for half time the tempo ( in mSec)
    
    MIDI.sendNoteOff(note, 0, channel);  // Stop the note
    
    digitalWrite(LED_BUILTIN, LOW); //Turn off the led
    
    delay(tempo/2);	        // Wait for half time the tempo ( in mSec)
    
}
