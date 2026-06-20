#ifndef DHT22SENSOR_H
#define DHT22SENSOR_H

#include <DHT.h>

#define DHTPIN  _____
#define DHTTYPE _____

class DHT22Sensor {
public:
    void begin();
    float readTemperature();
    float readHumidity();
private:
    DHT _dht{DHTPIN, DHTTYPE};
};

#endif
