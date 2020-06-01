#include "Sensors.h"

SENSORS::SENSORS(){}
SENSORS::~SENSORS(){}

HCSR04 hcsr04(TRIG_PIN, ECHO_PIN);

float SENSORS::readDistance(){

    float dist;
    float sum = 0.0;

    for(int i = 0; i < 10; i++){
        delay(20);
        float d = hcsr04.dist();
        delay(20);
        sum = sum + d;
    }
    dist = sum / 10;

    Serial.print(F("Distance: "));
    Serial.print(dist);
    Serial.print(F(" cm "));

    return dist;
}


uint16_t SENSORS::readLight(){
   
    // https://www.allaboutcircuits.com/projects/design-a-luxmeter-using-a-light-dependent-resistor/
    uint16_t ldrRawData;
    uint16_t sum = 0;

    for(int i = 0; i < 10; i++){
        delay(20);
        uint16_t l = analogRead(A0);
        delay(20);
        sum = sum + l;
    }
    ldrRawData = sum / 10;

    uint16_t MAX_ADC_READING = 1023;
    uint8_t ADC_REF_VOLTAGE = 5;
    float REF_RESISTANCE = 216.4;
    uint32_t LUX_CALC_SCALAR = 12518931;
    float LUX_CALC_EXPONENT = -1.405; 
    float resistorVoltage = (float)ldrRawData / MAX_ADC_READING * ADC_REF_VOLTAGE;
    float ldrVoltage = ADC_REF_VOLTAGE - resistorVoltage;
    float ldrResistance = ldrVoltage / resistorVoltage * REF_RESISTANCE; // REF_RESISTANCE is 216.4 ohm

    uint16_t ldrLux = LUX_CALC_SCALAR * pow(ldrResistance, LUX_CALC_EXPONENT);

    Serial.print(F("Light: "));
    Serial.print(ldrLux);
    Serial.println(F(" lux"));

    return ldrLux;
}