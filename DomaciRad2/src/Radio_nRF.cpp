#include "Radio_nRF.h"
#include "main.h"

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

RADIO::RADIO() {}
RADIO::~RADIO() {}

const byte address[6] = {"3node"};

void RADIO::nRF_init()
{
    radio.begin();
    radio.setDataRate(RF24_250KBPS);
    radio.setChannel(111);
    radio.setPALevel(RF24_PA_MAX);
    radio.setRetries(3, 5); // delay, count
    radio.openWritingPipe(address);
}

bool RADIO::RF_send(struct SensorData sensorData)
{
    //!!!your code goes here!!!
    /* ova funkcija šalje podatke preko radio kanala i vraća bool vrijednost ovisno o tome je li komunikacija bila uspješna.
    Trenutno vraća uvijek false, ali je potrebno zamijeniti false sa bool rezultatom radio komunikacije. */
    bool rslt;
    rslt = radio.write(&sensorData, sizeof(sensorData));

    Serial.print("Data Sent ");
    Serial.print(sensorData.temp);
    Serial.print(" ");
    Serial.print(sensorData.lightLevel);


    return rslt;
}

void RADIO::RF_receive(bool rslt)
{
    //!!!your code goes here!!!
    /* ova funkcija samo ispisuje je li rezultat komunikacije bio uspješan ili ne, odnosno je li primi acknowledgment ili ne */

    if (rslt){
       
        Serial.println("  Acknowledge received");

    } else{
        
        Serial.println("  Tx failed");

    }
}