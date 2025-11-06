#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();



int value;
int prevValue;
int ccNo = 105;
int channel = 14;
int velocity = 200;

int tempo = 100;

int minimumRange = 4;
int maximumRange = 1024;

int minimalMidiValue = 1;
int maximumMidiValue = 127;

bool debug = true;

uint16_t pentatonicTable[54] = { 0, 1, 3, 6, 8, 10, 13, 15, 18, 20, 22, 25, 27, 30, 32, 34, 37, 39, 42, 44, 46, 49, 51, 54, 56, 58, 61, 63, 66, 68, 70, 73, 75, 78, 80, 82, 85, 87, 90, 92, 94, 97, 99, 102, 104, 106, 109, 111, 114, 116, 118, 121, 123, 126 };

uint16_t mapPentatonic(uint16_t input) {
  uint8_t value = (1023 - input) / (1024 / 53);
  return (pentatonicTable[value]);
}

void setup() {
  Serial.begin(115200);

  // Initiate MIDI communications, listen to all channels
  MIDI.begin(MIDI_CHANNEL_OMNI);

  // wait until serial port opens for native USB devices
  while (!Serial) {
    delay(1);
  }

  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1)
      ;
  }
  // power
  Serial.println(F("VL53L0X API Simple Ranging example\n\n"));
}


void loop() {
  MIDI.read();
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
        prevValue = value;
        //MIDI.sendControlChange(ccNo, value, channel);
      }
    } else {
      if (debug) Serial.println(" out of range ");
    }

    delay(tempo/2);
    MIDI.sendNoteOff(127 - prevValue, 0, channel);
    delay(tempo/2);
  }
}
