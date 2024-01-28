#include <Arduino.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <config.h>

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    randomSeed(micros());

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *payload, unsigned int length) {
    Serial.println("Message arrived");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
}

void reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        String clientId = CLIENT_UUID + String("-") + String(random(0xffff), HEX);
        if (client.connect(clientId.c_str(), MQTT_SERVER_LOGIN, MQTT_SERVER_PASS)) {
            Serial.println("connected");
            client.subscribe(TOPIC);
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void setup() {
    pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
    Serial.begin(9600);
    setup_wifi();
    client.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
    client.setCallback(callback);
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
}
