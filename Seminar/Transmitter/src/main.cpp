#include <Arduino.h>
#include <LowPower.h>
#include "main.h"
#include "Sensors.h"
#include "Transmitter_nRF.h"
#include <avr/wdt.h>

#define N 1
#define N_max 10
#define DEV 0.2


SENSORS sensor;
RADIO radioNRF;


SensorData dataToSend;
PreSensorData preData;

StateType state = READ_SERIAL;

void compareWithPreviousValues();

bool rslt;
uint8_t counter;

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

      compareWithPreviousValues();
      wdt_reset();

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

void compareWithPreviousValues(){

  if (!((preData.preDist <= (dataToSend.distance + (DEV*dataToSend.distance))) && (preData.preDist >= (dataToSend.distance - (DEV*dataToSend.distance)))) || !((preData.preLight <= (dataToSend.lightLevel + (DEV*dataToSend.lightLevel))) &&(preData.preLight >= (dataToSend.lightLevel - (DEV*dataToSend.lightLevel)))))
  {
    rslt = radioNRF.RF_send(dataToSend);
    preData.preDist = dataToSend.distance;
    preData.preLight = dataToSend.lightLevel;
    counter = 0;
    state = RADIO_RX;
  } else if (counter >= N_max){
    rslt = radioNRF.RF_send(dataToSend);
    counter = 0;
    state = RADIO_RX;
  } else{
    Serial.println(F("Transmitter will not send data!!!"));
    counter++;
    state = SLEEP_STATE;
  }
  
}





