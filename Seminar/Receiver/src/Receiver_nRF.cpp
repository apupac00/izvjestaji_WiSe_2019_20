#include "Receiver_nRF.h"

const byte address[][6] = {"1node", "2node", "3node", "4node", "5node", "6node"};

RF24 radio(CE_PIN, CSN_PIN);


RADIO::RADIO() {
    newData = false;
}
RADIO::~RADIO() {}


void RADIO::nRF_init()
{
    Serial.println(F("SimpleRx Starting"));
    radio.begin();
    radio.setDataRate(RF24_250KBPS);
    radio.setChannel(111);
    radio.setPALevel(RF24_PA_MAX);
    radio.openReadingPipe(1, address[0]);
    radio.openReadingPipe(2, address[1]);
    radio.openReadingPipe(3, address[2]);
    radio.openReadingPipe(4, address[3]);
    radio.openReadingPipe(5, address[4]);
    radio.openReadingPipe(6, address[5]);
    radio.startListening();
}

void RADIO::getData(){
    uint8_t pipeNum;
    if (radio.available(&pipeNum))
    {
        radio.read(&dataReceived, sizeof(dataReceived));
        newData = true;
    }
}
void RADIO::showData()
{
    if (newData == true)
    {
        Serial.println(F("Received data"));
        Serial.print(F("D: "));
        Serial.println(dataReceived.distance);
        Serial.print(F("L: "));
        Serial.println(dataReceived.lightLevel);
        newData = false;
    }
}

