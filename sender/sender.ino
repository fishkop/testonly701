// #git@github.com:fishkop/testonly701.git

#include <Arduino.h>
#include <WString.h>

#include <esp_now.h>
#include <WiFi.h>

#include <HardwareSerial.h>


#define BUTTON_PIN 0

typedef struct struct_message {
    bool buttonState01;
    bool buttonState02;
} struct_message;



struct_message myData;


// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x30, 0xAE, 0xA4, 0x26, 0xBD, 0xC4}; 


void setup() {
    // Init Serial Monitor
    Serial.begin(115200);

    pinMode(BUTTON_PIN, INPUT_PULLUP);

    myData.buttonState02 = false;

    delay(2000);

    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("\n*** Error initializing ESP-NOW");
        return;
    }

    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 1;  // Valid channel range is 1 to 13
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("\n*** Failed to add peer");
        return;
    }
}


void loop() {

    /* This line of code reads the state of a digital input pin and assigns a boolean value 
       to myData.buttonState based on whether the pin is LOW. 
    */
    myData.buttonState01 = digitalRead(BUTTON_PIN) == LOW; 
    /* 1) digitalRead(BUTTON_PIN): This function reads the current state (HIGH or LOW) of the digital pin defined by BUTTON_PIN.
       2) digitalRead(BUTTON_PIN) == LOW: This expression evaluates to true if the pin state is LOW, and false otherwise.
       3) myData.buttonState = digitalRead(BUTTON_PIN) == LOW;: The result of the comparison (true or false) is assigned to myData.buttonState.
      In summary, myData.buttonState will be true if the button connected to BUTTON_PIN is pressed (assuming pressing the button pulls the pin LOW), and false otherwise.
    */

    /* myData.buttonState02 = !myData.buttonState02; inverts the value of myData.buttonState02. 
       Since false is equivalent to 0, !false is true, which is equivalent to 1. 
       Therefore, myData.buttonState02 is set to true.
    */
    myData.buttonState02 = !myData.buttonState02;
    

    // Send message via ESP-NOW
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

    if (result == ESP_OK) {
        Serial.println("Sent with success");
    } else {
        Serial.println("Error sending the data");
    }

    delay(2000);
}
