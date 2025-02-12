#include <Arduino.h>
#include "matrix/matrix.h"

#include <Ethernet.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <config.h>

#define NETWORK_DELAY_MSEC 5000
#define RGB_COLORS_COUNT 3
#define MAX_RECEIVE_MATRIX_WIDTH 16
#define MAX_RECEIVE_BUFFER_SIZE 2048

WiFiClient espClient;
PubSubClient client(espClient);
LedMatrix led_matrix;

/**
 * @brief Настройка WiFi
 *
 * Установка соединения с WiFi. 
 * Конфигурация берется из файла config.h
 */
void setup_wifi() {
    Serial.printf("Connecting to %s\n", WIFI_SSID);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED) {
        delay(NETWORK_DELAY_MSEC);
        Serial.print(".");
    }

    randomSeed(micros());
    Serial.printf("\nWiFi connected\nIP address: %s\n", WiFi.localIP().toString().c_str());
}

/**
 * @brief Обработка входящих сообщений
 *
 * Данная функция вызывается при обработке входящих сообщений
 * с MQTT брокера.
 * Итерируясь по набору байтов сериализует их в цвет. Каждая группа из 
 * 3 байтов считается за RGB цвет. При сериализации цвета устанавливает
 * цвет для текущей ячейки. 
 * После этого текущая просматриваемая ячейка изменяется (на следующую по горизонтали). 
 * Заполнение идет построчно-итеративно
 * Только при заполнении одной строки начинается заполнение следующей
 */
void callback(char *topic, byte *payload, int length) {
    byte tmpMod;
    byte oneCellRGB[RGB_COLORS_COUNT];
    int height = 0, width = 0;
    for (int receivedByteIndex = 0; receivedByteIndex < length; receivedByteIndex++) {
        tmpMod = receivedByteIndex % 3;
        if (receivedByteIndex > 0 && tmpMod == 0) {
            led_matrix.setColor(height, width, oneCellRGB[0], oneCellRGB[1], oneCellRGB[2]);
            width ++;
            if (width == MAX_RECEIVE_MATRIX_WIDTH)
            {
              height ++;
              width = 0;
            }
        }
        oneCellRGB[tmpMod] = payload[receivedByteIndex];
    }
    led_matrix.redraw();
}


/*
 * @brief Подключение к MQTT брокеру
 *
 * Подключается к MQTT брокеру, при неудаче уходит в таймаут
 * после пытается подключиться снова. 
 * Параметры подключения задаются в config.h
 *
 */
void reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        String clientId = CLIENT_UUID + String("-") + String(random(0xffff), HEX);
        if (client.connect(clientId.c_str(), MQTT_SERVER_LOGIN, MQTT_SERVER_PASS)) {
            Serial.println("connected");
            client.subscribe(TOPIC);
        } else {
            Serial.printf("Connection failed, rc=%d. Retrying in 5 seconds...\n", client.state());
            delay(NETWORK_DELAY_MSEC);
        }
    }
}

void setup() {
    // Initialize the BUILTIN_LED pin as an output
    pinMode(BUILTIN_LED, OUTPUT);
    Serial.begin(9600);
    setup_wifi();

    // PubSubClient configuration
    client.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
    client.setCallback(callback);
    client.setBufferSize(MAX_RECEIVE_BUFFER_SIZE);

    // LedMatrix configuration
    led_matrix.begin();
    led_matrix.clear();
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
}
