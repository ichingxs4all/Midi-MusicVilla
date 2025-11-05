// -----------------------------------------------------------------------------

// This function will be automatically called when a NoteOn is received.
// It must be a void-returning function with the correct parameters,
// see documentation here:
// https://github.com/FortySevenEffects/arduino_midi_library/wiki/Using-Callbacks

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
    // Do whatever you want when a note is pressed.
    digitalWrite(LED_BUILTIN, HIGH);
    MIDI.sendNoteOn(pitch, velocity, channel);    // Send a Note (pitch 42, velo 127 on channel 1)
    // Try to keep your callbacks short (no delays ect)
    // otherwise it would slow down the loop() and have a bad impact
    // on real-time performance.
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
    // Do something when the note is released.
    // Note that NoteOn messages with 0 velocity are interpreted as NoteOffs.
    digitalWrite(LED_BUILTIN, LOW);
    MIDI.sendNoteOff(pitch, velocity, channel);  
}

void handleControlChange( byte channel, byte number, byte value)
{


}

void handleClock(){ 
   
   if(click == step){
   MIDI.sendNoteOn(64,127,1);
   delay(20);
   MIDI.sendNoteOff(64,0,1);
   click=0;
   }
   click++;
}

void handleStart(){ 

}

void handleStop(){ 

}

void handleContinue(){ 

}

// -----------------------------------------------------------------------------
