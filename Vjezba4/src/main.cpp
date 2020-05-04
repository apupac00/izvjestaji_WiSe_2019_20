#include <Arduino.h>

class Flasher
{
  int ledPin;   // the number of the LED pin
  long OnTime;  // milliseconds of on-time
  long OffTime; // milliseconds of off-time

  int ledState; // ledState used to set the LED
  unsigned long previousMillis;

public:
  Flasher(int pin, long onTime, long offTime)
  {
    ledPin = pin;
    OnTime = onTime;
    OffTime = offTime;
    ledState = LOW;
    previousMillis = 0;
    pinMode(ledPin, OUTPUT);
  }
  ~Flasher() {}
  void Update(unsigned long currentMillis)
  {

    if ((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
      ledState = LOW;                 // Turn it off
      previousMillis = currentMillis; // Remember the time
      digitalWrite(ledPin, ledState); // Update the actual LED
    }
    else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
    {
      ledState = HIGH;                // turn it on
      previousMillis = currentMillis; // Remember the time
      digitalWrite(ledPin, ledState); // Update the actual LED
    }
  }
};

Flasher ledB(13, 200, 500);
Flasher ledR(12, 125, 365);
Flasher ledG(11, 221, 655);

void setup()
{
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);
}

void loop()
{
}
SIGNAL(TIMER0_COMPA_vect)
{
  unsigned long currentMillis = millis();

  ledB.Update(currentMillis);
  ledR.Update(currentMillis);
  ledG.Update(currentMillis);
}
