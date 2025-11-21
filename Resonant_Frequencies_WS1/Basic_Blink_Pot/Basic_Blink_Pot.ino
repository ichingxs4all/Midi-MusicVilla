//Simple example of blinking a led in a rhythm of the position of a potentiometer
//By Michel Gutlich for the workshop Resonant Frequencies #2

#define LED_BUILTIN 3
#define SENSORPIN A0

const bool debug = true;

int tempo = 500;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  if (debug) Serial.begin(115200);
  analogReference(EXTERNAL); //Set the analog reference to external so we can use 3.3 volts as a reference. A wire must be connected from the ARef pin to 3.3V
}

// the loop function runs over and over again forever
void loop() {
  tempo = analogRead(SENSORPIN);  //Read the value of the potentiometer ( 0 - 1023)

  if(debug) Serial.println(tempo);

  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(tempo/2);                      // wait for half the tempo
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(tempo/2);                      // wait for half the tempo
}

//Experiment:
//Invert one or both of  the delay lines  the tempo value by writing it as 
// delay(512 - tempo/2);

