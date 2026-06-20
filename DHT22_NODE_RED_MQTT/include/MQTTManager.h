#ifndef MQTTMANAGER_H
#define MQTTMANAGER_H

#include <WiFi.h>
#include <PubSubClient.h>


// ===== ตั้งค่า WiFi + MQTT =====
#define WIFI_SSID       "YOUR_WIFI_SSID"
#define WIFI_PASSWORD   "YOUR_WIFI_PASSWORD"
#define MQTT_SERVER     "broker.emqx.io"
#define MQTT_PORT       1883
#define TOPIC_SENSORS   "SENSORS_TOPIC"
#define TOPIC_COMMANDS  "COMMANDS_TOPIC"

class MQTTManager {
public:
    void begin(void (*callback)(char*, byte*, unsigned int));
    void loop();
    bool publish(const char* topic, const char* payload);
    bool connected();
private:
    void connectWiFi();
    void connectMQTT();
    WiFiClient    _wifiClient;
    PubSubClient  _client{_wifiClient};
    void (*_callback)(char*, byte*, unsigned int) = nullptr;
};

#endif
