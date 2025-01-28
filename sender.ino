// #git@github.com:fishkop/testonly701.git

#include <Arduino.h>
#include <WString.h>

#include <esp_now.h>
#include <WiFi.h>

#include <HardwareSerial.h>


#define BUTTON_PIN 0

typedef struct struct_message {
    bool buttonState;
} struct_message;

struct_message myData;


// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x24, 0x6F, 0x28, 0xAE, 0x4C, 0xD4}; 


void setup() {
    // Init Serial Monitor
    Serial.begin(115200);

    pinMode(BUTTON_PIN, INPUT_PULLUP);

    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }
}


void loop() {
    myData.buttonState = digitalRead(BUTTON_PIN) == LOW;
    

    // Send message via ESP-NOW
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

    if (result == ESP_OK) {
        Serial.println("Sent with success");
    } else {
        Serial.println("Error sending the data");
    }

    delay(2000);
}
