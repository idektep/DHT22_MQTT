#include <Arduino.h>
#include "LED.h"
#include "Buzzer.h"
#include "DHT22Sensor.h"
#include "MQTTManager.h"

// ===== Class object =====
LED          led;
BUZZER       buzzer;
DHT22Sensor  dhtSensor;
MQTTManager  mqtt;

// ===== ตัวแปรเวลา =====
unsigned long lastSend = 0;
const unsigned long SEND_INTERVAL = 2000; // ส่งข้อมูลทุก 2 วินาที

// ===== Callback รับคำสั่งจาก MQTT =====
void mqttCallback(char* topic, byte* payload, unsigned int length) {
    String incoming = "";
    for (unsigned int i = 0; i < length; i++)
        incoming += (char)payload[i];

    Serial.println("MQTT CMD: " + incoming);

    if (incoming == "LED_ON") {
        led.led_on(0);
        Serial.println("LED ON");
    } else if (incoming == "LED_OFF") {
        led.led_off(0);
        Serial.println("LED OFF");
    } else if (incoming == "BUZZER_ON") {
        buzzer.buzzer_on(0);
        Serial.println("Buzzer ON");
    } else if (incoming == "BUZZER_OFF") {
        buzzer.buzzer_off(0);
        Serial.println("Buzzer OFF");
    }
}

// ===== ฟังก์ชันส่งข้อมูล DHT22 ผ่าน MQTT =====
void publishSensorData() {
    float temp = dhtSensor.readTemperature();
    float hum  = dhtSensor.readHumidity();

    if (isnan(temp) || isnan(hum)) {
        Serial.println("DHT22 read error!");
        return;
    }

    // สร้าง JSON payload
    char payload[128];
    snprintf(payload, sizeof(payload),
             "{\"temp\":%.1f,\"hum\":%.0f}",
             temp, hum);

    mqtt.publish(TOPIC_SENSORS, payload);

    Serial.print("Published: ");
    Serial.println(payload);
}

// ===== Setup =====
void setup() {
    Serial.begin(115200);

    // เริ่มต้นอุปกรณ์ Week3
    led.ledpinsetup();
    buzzer.buzzerpinsetup();

    // เริ่มต้น DHT22
    dhtSensor.begin();
    Serial.println("DHT22 initialized");

    // เริ่มต้น WiFi + MQTT
    mqtt.begin(mqttCallback);
    Serial.println("System ready!");
}

// ===== Loop =====
void loop() {
    mqtt.loop(); // ดูแล WiFi/MQTT reconnect + รับข้อความ

    // ส่งข้อมูลเซนเซอร์ทุก 2 วินาที
    if (millis() - lastSend >= SEND_INTERVAL) {
        lastSend = millis();
        publishSensorData();
    }

    // Blink LED ตามปกติของ Week3 (ทุก 1 วินาที)
    led.led_on(500);
    led.led_off(500);
}
