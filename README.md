# testonly701
test only code from copilot


Ccontext + Task:

I want to use two ESP32 with WIFInow. 
The first ESP has a button. every time the button is press, the status has transfered ro the second EXP32 board viw WIFInow. 
the second board receives the status of the button of the first ESP32 board and set an output with LED according the status on or off.



GitHub Copilot:

To achieve this, you can use the ESP-NOW protocol, which is a connectionless communication protocol developed by Espressif. 
Below are the steps and code snippets for both ESP32 boards.

Steps:
Set up the first ESP32 to send the button status via ESP-NOW.
Set up the second ESP32 to receive the button status and control an LED accordingly.


File 1:   Code for the First ESP32 (sender)

File 2:   Code for the Second ESP32 (Receiver)


Instructions:
Replace the broadcastAddress in the sender code with the MAC address of the receiver ESP32.
Upload the sender code to the first ESP32.
Upload the receiver code to the second ESP32.
Connect a button to the BUTTON_PIN (GPIO 0) on the first ESP32.
Connect an LED to the LED_PIN (GPIO 2) on the second ESP32.
When the button on the first ESP32 is pressed, the status will be sent to the second ESP32, 
which will turn the LED on or off accordingly.


Similar code found with 1 license type - View matches
