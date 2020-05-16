#include "Radio_nRF.h"
#include "main.h"

RF24 radio(CE_PIN, CSN_PIN);

RADIO::RADIO() {}
RADIO::~RADIO() {}

const byte address[6] = {"3node"};

void RADIO::nRF_init()
{
    radio.begin();
    radio.setDataRate(RF24_250KBPS);
    radio.setChannel(111);
    radio.setPALevel(RF24_PA_MAX);
    radio.setRetries(3, 5);
    radio.openWritingPipe(address);
}

bool RADIO::RF_send(struct SensorData sensorData)
{
    bool rslt;

    delay(50);
    rslt = radio.write(&sensorData, sizeof(sensorData));
    delay(50);

    Serial.print(F("Data Sent "));
    Serial.print(sensorData.distance);
    Serial.print(F(" "));
    Serial.print(sensorData.lightLevel);

    return rslt;
}

void RADIO::RF_receive(bool rslt)
{
    if(rslt) {

        Serial.println(F(" Acknowledge received"));
        
    } else{
        
        Serial.println(F(" Tx failed"));

    }
}