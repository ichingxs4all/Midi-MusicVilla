//Simple example to use a distance sensor as a way of playing notes
//Made by Michel Gutlich for the Resonant Frequencies WS #1 

//#define LED_BUILTIN 3
#define VELOCITYPIN A1

//Include the FortySevenEffects MIDI library through the library manager
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

//Include the Adafruit VL53L0X sensor library through the library manager

#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

int value; //This will store the sensor value
int prevValue; //This will hold the last sensor value read

int ccNo = 105; //The control change parameter number
int channel = 1; //The MIDI channel we are going to send on
int velocity = 100; //The initial velocity ammount we are goin to use

int tempo = 100; //This will control the length of the notes played

int minimumRange = 4; //This is the minimum sensor value used
int maximumRange = 1024; //This is the maximum sensor value used

int minimalMidiValue = 1; //This is the minimum value of the midi control change parameter
int maximumMidiValue = 127; //This is the maximum value of the midi control change parameter

bool debug = true; //Set this to false to disable debugging through the serial port

//An array of midi notes in the pentatonic range
#define NUMNOTES 53
uint16_t pentatonicTable[54] = { 0, 1, 3, 6, 8, 10, 13, 15, 18, 20, 22, 25, 27, 30, 32, 34, 37, 39, 42, 44, 46, 49, 51, 54, 56, 58, 61, 63, 66, 68, 70, 73, 75, 78, 80, 82, 85, 87, 90, 92, 94, 97, 99, 102, 104, 106, 109, 111, 114, 116, 118, 121, 123, 126 };

//Function of mapping the sensor value in a scale of MIDI
uint16_t mapPentatonic(uint16_t input) {
  uint8_t value = ((maximumRange -1) - input) / (maximumRange / NUMNOTES);
  return (pentatonicTable[value]);
}

void setup() {
  if(debug) Serial.begin(115200);

  // Initiate MIDI communications, listen to all channels
  MIDI.begin(MIDI_CHANNEL_OMNI);

  // wait until serial port opens for native USB devices
  while (!Serial) {
    delay(1);
  }

  if(debug)Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    if(debug)Serial.println(F("Failed to boot VL53L0X"));
    while (1)
      ;
  }
  // power
  if(debug)Serial.println(F("VL53L0X API Simple Ranging example\n\n"));
}


void loop() {
  MIDI.read();
  //velocity = map(analogRead( VELOCITYPIN), 0 , 1023 , 0 , 127);

  VL53L0X_RangingMeasurementData_t measure;

  lox.rangingTest(&measure, false);  // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    value = measure.RangeMilliMeter;
    if (debug) Serial.println(value);
    if (value > minimumRange && value < maximumRange) {
      //value = map(value, minimumRange ,maximumRange , minimalMidiValue , maximumMidiValue);
      value = mapPentatonic(value);
      if (value != prevValue) {
        MIDI.sendNoteOn(127 - value, velocity, channel);
        //MIDI.sendControlChange(ccNo, value, channel);
      }
        prevValue = value;
       
      }
    } else {
      if (debug) Serial.println(" out of range ");
    }

    delay(tempo/2);
    MIDI.sendNoteOff(127 - prevValue, 0, channel);
    delay(tempo/2);
  }

