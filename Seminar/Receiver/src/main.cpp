// SimpleRx - the slave or the receiver

#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "Receiver_nRF.h"

RADIO radioNRF;

void setup()
{
  Serial.begin(115200);
  radioNRF.nRF_init();
 
}

void loop()
{
  radioNRF.getData();
  radioNRF.showData();
}

