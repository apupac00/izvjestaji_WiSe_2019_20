#include "Sensors.h"

DHT dht(DHTPIN, DHTTYPE);

BH1750 lightMeter(0x23);

SENSORS::SENSORS(){};
SENSORS::~SENSORS(){};

void SENSORS::DHT_init(){
    Serial.println(F("DHTxx test!"));
    dht.begin();
}
void SENSORS::BH1750_init(){

    lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);
    Serial.println(F("BH1750 Test"));
}

void SENSORS::readTempHum(){
    uint8_t h;
    uint8_t t;

    delay(2000);

    h = dht.readHumidity();
    t = dht.readTemperature();

    if (isnan(h) || isnan(t))
    {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }

    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.print(F(" %\t"));
    Serial.print(F("Temperature: "));
    Serial.print(t);
    Serial.print(F(" *C "));
}

void SENSORS::readLight(){
    uint16_t lux;

    lux = lightMeter.readLightLevel();
    Serial.print(F("Light: "));
    Serial.print(lux);
    Serial.println(F(" lx"));

    Serial.print(F("Free SRAM: "));
    Serial.print(freeRam());
    Serial.print(F(" bytes"));
}
int SENSORS::freeRam()
{
    extern int __heap_start, *__brkval;
    int v;
    return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}