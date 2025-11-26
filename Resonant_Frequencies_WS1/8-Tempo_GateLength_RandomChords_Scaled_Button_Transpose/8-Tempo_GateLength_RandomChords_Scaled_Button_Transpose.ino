// Simple example of playing a random  MIDI chords in a certain scale on channel 1 in a tempo based on the level of a potentiometer ( sensor) attached to A0;
// The gatelength is controlled by a lightsensor connected to A1
// A button connected to pin 5 transposes a certain amount
//by Michel Gutlich for the Resonant Frequencies workshop #2

#define LED_BUILTIN 3 // A led is attached to pin 3 to have some visual indication of what is happening
#define SENSORPIN A0 //A potentiomter connected to A0
#define GATEPIN A1 //A lightsensor connected to A1
#define BUTTONPIN 5 //A button connected to pin 5

// We are goin to use the FortySevenEffects MIDI library. Make sure it downloaded and installed through the Library Manager
//https://github.com/FortySevenEffects/arduino_midi_library
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE(); //Create a standard instance of a hardware Serial Port MIDI device

int tempo = 500; // Declare the variable 'tempo' and give it the initial value of 500 mSec;

int channel = 1; //The MIDI channel we are going to send messages to. Make this the channel number your synthesizer is set on. Channel numbers are between 1 and 16

int noteA = 42; //The note number we are going send. Note numbers are between 0 and 127
int noteB = 42; //The note number we are going send. Note numbers are between 0 and 127
int noteC = 42; //The note number we are going send. Note numbers are between 0 and 127

int velocity = 127; //The velocity ( volume) of the note we are going to send. Velocty value are between 0 and 127 

int gateLength = 20;

bool debug = true; //Set this to false to turn off debugging to the USB serial port

int numNotesInScale; //This will hold the number of notes in a scale 

int scale = 1 ; //This parameter will set the type of scale , 0 = chromatic, 1 = pentatatonic and 2 = blues scale
int range = 12; //The range of the random notes to be selected
int transpose = 32; //Transpose the range to a certain place on the scale

int playing;

void setup()
{
    if(debug) Serial.begin(115200); //Setup the USB serial port for debugging if the boolean 'debug' is true

    pinMode(LED_BUILTIN, OUTPUT);    //Set the pin where the led is attached to as an output
    pinMode (BUTTONPIN,INPUT);
    MIDI.begin(MIDI_CHANNEL_OMNI);   // Launch MIDI and listen on all channels
    analogReference(EXTERNAL); //Set the analog reference to external so we can use 3.3 volts as a reference. A wire must be connected from the ARef pin to 3.3V
}

void loop()
{
    if ( digitalRead(BUTTONPIN))transpose = 24; else transpose = 32; //Check if button is pressed and transpose according

    MIDI.read();            // Listen for incomming MIDI messages. It's a good thing to always implement this function in your own code
    
    tempo = analogRead(SENSORPIN); // Read analog port A0 and put the value in the parameter tempo. The value will be between 0 and 1023

    gateLength = analogRead(GATEPIN)/5; // Read analog port A1 and put the value in the parameter velocity. The value will be between 0 and 1023 zo we have to divide it by a scale factor to be in range

    if(debug) Serial.println(gateLength); //Send the value to the USB Serial portfor debugging if the boolean 'debug' is true

    noteA = setScale(random(range), scale, transpose); //Choose a random note number between 0 and 127, scale it and transpose it 
    noteB = setScale(random(range), scale, transpose); //Choose a random note number between 0 and 127, scale it and transpose it 
    noteC = setScale(random(range), scale, transpose); //Choose a random note number between 0 and 127, scale it and transpose it 

    digitalWrite(LED_BUILTIN, HIGH); //Turn the led on
    
    MIDI.sendNoteOn(noteA, velocity, channel);    // Send the note with a velocity on a channel
    MIDI.sendNoteOn(noteB, velocity, channel);    // Send the note with a velocity on a channel
    MIDI.sendNoteOn(noteC, velocity, channel);    // Send the note with a velocity on a channel
    
    delay(gateLength);		    // Wait for the amount of gate length
    
    MIDI.sendNoteOff(noteA, 0, channel);  // Stop the note
    MIDI.sendNoteOff(noteB, 0, channel);  // Stop the note
    MIDI.sendNoteOff(noteC, 0, channel);  // Stop the note
    
    digitalWrite(LED_BUILTIN, LOW); //Turn off the led
    
    delay(tempo - gateLength);	        // Wait for an amount of time minus the gate length
    
}

//Experiments:
//Play arpegios instead of chords ( hint: place delay's in betweenthe notes)

