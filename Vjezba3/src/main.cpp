#include "Sensors.h"
#include <LowPower.h>

SENSORS sensors;

void setup()
{
  Serial.begin(115200);
  sensors.DHT_init();
  sensors.BH1750_init();
  delay(100); // give some time to send data over Serial before going to sleep
}


void loop()
{
  sensors.readTempHum();
  sensors.readLight();

  delay(50);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  delay(50);
}



