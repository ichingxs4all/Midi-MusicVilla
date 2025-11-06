// -----------------------------------------------------------------------------

// This function will be automatically called when a NoteOn is received.
// It must be a void-returning function with the correct parameters,
// see documentation here:
// https://github.com/FortySevenEffects/arduino_midi_library/wiki/Using-Callbacks

void handleNoteOn(byte channel, byte note, byte velocity) {
  // Do whatever you want when a note is pressed.
  digitalWrite(LED_BUILTIN, HIGH);
  // if(debug) Serial.println(note); //Send the value to the USB Serial portfor debugging if the boolean 'debug' is true
  MIDI.sendNoteOn(note, velocity, channel);  // Send the note with a velocity on a channel

  // Try to keep your callbacks short (no delays ect)
  // otherwise it would slow down the loop() and have a bad impact
  // on real-time performance.
}

void handleNoteOff(byte channel, byte note, byte velocity) {
  MIDI.sendNoteOff(note, 0, channel);  // Stop the note
  digitalWrite(LED_BUILTIN, LOW);      //Turn off the led
}

void handleControlChange(byte channel, byte number, byte value) {
}

void handleClock() {
  if (playStatus == 1) {
    if (click == step) {

      velocity = analogRead(VELOCITYPIN) / velScale;  // Read analog port A1 and put the value in the parameter velocity. The value will be between 0 and 1023 zo we have to divide it by a scale factor to be in range

      note = setScale(random(12), scale, transpose);  //Choose a random note number between 0 and 127, scale it and transpose it

      handleNoteOn(channel, note, velocity);  //Play the calculated note

      clock_timer = millis();  //Store the current time in milliseconds in clock_timer to compare it later with the elapsed time to

      lastNotePlayed = note;  // Remember the last played note

      click = 0;  //Reset the click counter
    }

    click++;  //Advance the click counter by 1
  }
}

void handleStart() {
  playStatus = 1;  //Set the play status to 1 ( playing)
  if (debug) Serial.println("Playing");
}

void handleStop() {
  playStatus = 0;  //Set the play status to 0 ( stopped)
  click = 0;       //Reset the click counter -> If we restart we start from the beginning
  if (debug) Serial.println("Stopped");
}


void handleContinue() {
  playStatus = 2;  //Set the play status to 2 ( continue), we start were we left off
  if (debug) Serial.println("Continu");
}