#include <Arduino.h>
#include "MQTTManager.h"

void MQTTManager::begin(void (*callback)(char*, byte*, unsigned int)) {
    _callback = callback;
    connectWiFi();
    _client.setServer(MQTT_SERVER, MQTT_PORT);
    _client.setCallback(_callback);
}

void MQTTManager::loop() {
    if (WiFi.status() != WL_CONNECTED) connectWiFi();
    if (!_client.connected()) connectMQTT();
    _client.loop();
}

bool MQTTManager::publish(const char* topic, const char* payload) {
    if (!_client.connected()) return false;
    return _client.publish(topic, payload);
}

bool MQTTManager::connected() {
    return _client.connected();
}

void MQTTManager::connectWiFi() {
    Serial.print("Connecting WiFi");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(250);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected: " + WiFi.localIP().toString());
}

void MQTTManager::connectMQTT() {
    Serial.print("Connecting MQTT...");
    String clientId = "ESP32-" + String((uint32_t)ESP.getEfuseMac(), HEX);
    if (_client.connect(clientId.c_str())) {
        Serial.println("connected");
        _client.subscribe(TOPIC_COMMANDS);
    } else {
        Serial.print("failed, rc=");
        Serial.println(_client.state());
        delay(3000);
    }
}
