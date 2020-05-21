#ifndef main_h
#define main_h

struct SensorData
{
    uint16_t distance; 
    uint16_t lightLevel;
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