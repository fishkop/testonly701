// #git@github.com:fishkop/testonly701.git

#include <esp_now.h>
#include <WiFi.h>

#define LED_PIN 2

typedef struct struct_message {
    bool buttonState01;
    bool buttonState02;
} struct_message;

struct_message myData;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
    memcpy(&myData, incomingData, sizeof(myData));
    Serial.print("Button state: ");
    Serial.println(myData.buttonState);

    digitalWrite(LED_PIN, myData.buttonState ? HIGH : LOW);
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);

    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
    // Nothing to do here
}
