#include <Arduino.h>
#include <avr/wdt.h>

void setup() {
  Serial.begin(9600);
  Serial.println("Hello setup");

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  wdt_enable(WDTO_1S);
}

// the loop function runs over and over again forever
void loop() {
  Serial.println("Hello loop");
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second

  wdt_reset();                    
}