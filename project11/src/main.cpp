#include "Sensors.h"

SENSORS sensors;

void setup()
{
  Serial.begin(9600);
  sensors.DHT_init();
  sensors.BH1750_init();
  delay(100);
}

void loop()
{
  sensors.readTempHum();
  sensors.readLight();
}

