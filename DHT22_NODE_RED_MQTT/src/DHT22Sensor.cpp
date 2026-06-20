#include <Arduino.h>
#include "DHT22Sensor.h"

void DHT22Sensor::begin() {
    _dht.begin();
}

float DHT22Sensor::readTemperature() {
    return _dht.readTemperature();
}

float DHT22Sensor::readHumidity() {
    return _dht.readHumidity();
}
