//Simple example of blinking a led in a rhythm of 1 second
//By Michel Gutlich for the workshop Resonant Frequencies #2

#define LED_BUILTIN 3

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second
}


// Experiments:
// Try different values in the delay function
//
// Write the line with the delay function as:
// delay(random(1000));
