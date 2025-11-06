#define BTN_A 2
#define BTN_B 3
#define BTN_C 4

#define LED_BUILTIN 6
#define CLK_LED 7

#define POT_A A0
#define POT_B A1

#define CNTRL_NO_A 10
#define CNTRL_NO_B 11


#include <MIDI.h>

// Simple tutorial on how to receive and send MIDI messages.
// Here, when receiving any message on channel 4, the Arduino
// will blink a led and play back a note for 1 second.

MIDI_CREATE_DEFAULT_INSTANCE();


int step = 8;
int click =0;

int potA_Value;
int potB_Value;
int prevPotA_Value;
int prevPotB_Value;

bool button_a;
bool button_b;
bool button_c;

int channel = 1;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN,HIGH);
    pinMode(CLK_LED, OUTPUT);
    digitalWrite(CLK_LED,HIGH);
     // Connect the handleNoteOn function to the library,
    // so it is called upon reception of a NoteOn.
    MIDI.setHandleNoteOn(handleNoteOn);  // Put only the name of the function

    // Do the same for NoteOffs
    MIDI.setHandleNoteOff(handleNoteOff);

    MIDI.setHandleControlChange(handleControlChange);

    MIDI.setHandleClock(handleClock);
    MIDI.setHandleStart(handleStart);
    MIDI.setHandleContinue(handleContinue);
    MIDI.setHandleStop(handleStop);

    // Initiate MIDI communications, listen to all channels
    MIDI.begin(MIDI_CHANNEL_OMNI);
}                    

void loop()
{
    MIDI.read();  
    check_buttons();
    check_pots();     
    if (potA_Value != prevPotA_Value) {
        MIDI.sendControlChange( CNTRL_NO_A, potA_Value/8, channel ); 
        prevPotA_Value = potA_Value;       
    }
     if (potB_Value != prevPotB_Value) {
        MIDI.sendControlChange( CNTRL_NO_B, potB_Value/8, channel ); 
        prevPotB_Value = potB_Value;       
    }
    
    if (button_a) handleStart();
    if (button_b) handleStop();
    if (button_c) handleContinue();
}

void check_buttons(){
  button_a=digitalRead(BTN_A);
  button_b=digitalRead(BTN_B);
  button_c=digitalRead(BTN_C);
}

void check_pots(){
potA_Value = analogRead(POT_A);
potB_Value = analogRead(POT_B);

}