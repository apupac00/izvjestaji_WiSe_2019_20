#include <Arduino.h>
#include <LowPower.h>
#include "main.h"
#include "Sensors.h"
#include "Transmitter_nRF.h"
#include <avr/wdt.h>

#define N 1

SENSORS sensor;
RADIO radioNRF;


SensorData dataToSend;

StateType state = READ_SERIAL;

bool rslt;

void setup() {

  Serial.begin(115200);
  radioNRF.nRF_init();
  wdt_enable(WDTO_4S);

}


void loop() {

  switch (state) {
    
    case READ_SERIAL:
      state = READ_SENSORS;
      break;
    
    case READ_SENSORS:

      dataToSend.distance = sensor.readDistance();
      dataToSend.lightLevel = sensor.readLight();

      state = RADIO_TX;
      wdt_reset();
      break;

    case RADIO_TX:

      rslt = radioNRF.RF_send(dataToSend);
      wdt_reset();
      state = RADIO_RX;
      break;
    case RADIO_RX:

      radioNRF.RF_receive(rslt);
      state = SLEEP_STATE;
      break;
    case SLEEP_STATE:
      for(int i = 0; i < N; i++){
        delay(50);
        LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
        delay(50);
      }
      
      state = READ_SERIAL;
      break;

    default:
    
      break;
  }
  
}




