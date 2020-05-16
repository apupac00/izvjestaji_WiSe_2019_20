#ifndef main_h
#define main_h

struct SensorData
{
    float distance;
    uint32_t lightLevel;
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