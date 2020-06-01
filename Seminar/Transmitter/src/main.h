#ifndef main_h
#define main_h

struct SensorData
{
    float distance;
    uint16_t lightLevel;
};
struct PreSensorData{
    float preDist; 
    uint16_t preLight;
};
typedef enum
{
    READ_SERIAL,
    READ_SENSORS,
    SLEEP_STATE,
    RADIO_TX,
    RADIO_RX
} StateType;

#endif