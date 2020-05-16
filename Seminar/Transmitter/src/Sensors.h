#ifndef Sensors_h
#define Sensors_h

#include <Adafruit_Sensor.h>
#include <HCSR04.h>


#define TRIG_PIN 3
#define ECHO_PIN 4


class SENSORS {
public:

    SENSORS();
    ~SENSORS();
    float readDistance();
    uint32_t readLight();

};

#endif