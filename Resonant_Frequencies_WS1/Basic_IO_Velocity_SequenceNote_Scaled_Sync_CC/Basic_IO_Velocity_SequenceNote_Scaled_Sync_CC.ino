// Simple example of playing a sequenced or a random  MIDI note on a certain scale and in a tempo based on MIDI clock sync. The level of a potentiometer ( sensor) controls a control change parameter;
//The touch sensor on D6 enables/disables the randomiser
//by Michel Gutlich for the Resonant Frequencies workshop #1

#define LED_BUILTIN 3  // A led is attached to pin 3 to have some visual indication of what is happening
#define SENSORPIN A0 //The analog port used for reading the analog sensor
#define VELOCITYPIN A1
#define TOUCHPIN 6

// We are goin to use the FortySevenEffects MIDI library. Make sure it downloaded and installed through the Library Manager
//https://github.com/FortySevenEffects/arduino_midi_library
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();  //Create a standard instance of a hardware Serial Port MIDI device

int channel = 1;  //The MIDI channel we are going to send messages to. Make this the channel number your synthesizer is set on. Channel numbers are between 1 and 16

int numberOfNotes = 8;  //The number of note in the sequence
int note [] = {42, 46, 48, 44, 48, 46, 54, 54 } ;  //The note number we are going send. Note numbers are between 0 and 127

int seqStep = 0; //This will hold the actual sequence step we are in

int velocity = 100;  //The velocity ( volume) of the note we are going to send. Velocty value are between 0 and 127

int velScale = 4;  // scale factor for the velocity readings

bool debug = true;  //Set this to false to turn off debugging to the USB serial port

int numNotesInScale;  //This will hold the number of notes in a scale

int scale = 1;  //This parameter will set the type of scale , 0 = chromatic, 1 = pentatatonic and 2 = blues scale

int playing;  //This will hold a temporary value of the note  that is selected for playing after mapping it to a scale

int step = 8;  //MIDI clock is defined at 24 'clicks' for a quarter note. This is the number of 'clicks' that stands for a step

int click = 0;  // This will hold the MIDI clock clicks count

int playStatus = 1; // //This is our play status ; 0 = stopped , 1 = playing , 2 = continue ( does not reset the click count, so start were it left off)

int gateLength = 50; //This holds the gate length of the notes we are playing

int lastNotePlayed; //This will hold the last note played

long clock_timer; //This will store our clock timer value

int transpose = 24; //The amount of notes transposed according to the root note

int ccNo = 105; //This holds the control change number of the parameter of the synth we are going to change

int ccValue; //This will hold the value of the control change message
int lastCcValue; //This holds the last control change value we sended
int minSensorValue = 0; //This will hold the minimum value of the sensor being read
int maxSensorValue = 1023;  //This will hold the maximum value of the sensor being read
int minCcValue = 0; //This is the minimum control change value thats being send
int maxCcValue = 127; //This is the maximum control change value thats being send

bool randomiserOn = false; //This hold the status of the randomiser, it's default value is OFF

void setup() {
  if (debug) Serial.begin(115200);  //Setup the USB serial port for debugging if the boolean 'debug' is true


  pinMode(LED_BUILTIN, OUTPUT);  //Set the pin where the led is attached to as an output
  pinMode(TOUCHPIN,INPUT_PULLUP);

  // Connect the handleNoteOn function to the library,
  // so it is called upon reception of a NoteOn.
  MIDI.setHandleNoteOn(handleNoteOn);  // Put only the name of the function

  // Do the same for NoteOffs
  MIDI.setHandleNoteOff(handleNoteOff);
  // Connect the handleControlChange function to the library, so it is called upon reception of a ControlChange.
  MIDI.setHandleControlChange(handleControlChange);
  //The same for the reception of clock, start, stop and continue
  MIDI.setHandleClock(handleClock);
  MIDI.setHandleStart(handleStart);
  MIDI.setHandleContinue(handleContinue);
  MIDI.setHandleStop(handleStop);

  MIDI.begin(MIDI_CHANNEL_OMNI);  // Launch MIDI and listen on all channels
}

void loop() {
  
  MIDI.read();  // Listen for incomming MIDI messages. It's a good thing to always implement this function in your own code
  
  ccValue = map( analogRead(SENSORPIN), minSensorValue, maxSensorValue ,minCcValue, maxCcValue); //Map the sensor value to a certain range 


//Check the touch sensor to enable or disable the randomiser
  if(digitalRead(TOUCHPIN)){ //Check if the sensor is ouched
    if(debug)Serial.println("Randomiser ON");
    randomiserOn = 1; //Switch the randomsier on
  }else {
    if(debug )Serial.println("Randomiser OFF");
    randomiserOn = 0; //Switch the randomsier off
  }
 
  //Because we don't want to miss any clock pulses we make sure the last played note is turned off after the amount off gateLength
  if ((clock_timer > 0) && (millis() - clock_timer >= gateLength)) {
    handleNoteOff(channel, lastNotePlayed, 0); //Send note off for the last played note
    digitalWrite(LED_BUILTIN, LOW);  //Turn off the led
    clock_timer = 0; //Reset the clock timer
  }
}
