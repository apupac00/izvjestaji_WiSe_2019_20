#ifndef Receiver_nRF_h
#define Receiver_nRF_h

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 9
#define CSN_PIN 10

struct SensorData{
  float distance;
  uint16_t lightLevel;
};

class RADIO
{
public:
    struct SensorData dataReceived;

    bool newData;
    RADIO();
    ~RADIO();
    void nRF_init();
    void getData();
    void showData();

};

#endif