#include "can.h"
#include "data.h"
#include "ota.h"
#include "screen.h"
#include "touch.h"
// creo que estoy usando vspi
// pantalla tft_miso:nada tft_mosi:d13 tft_sclk:d14 tft_cs:d4 tft_dc:d32
// tft_rst:nada tft_bl:3v touch_sda:d21 touch_scl:d22 touch_int:d25
// touch_rst:nada mcp2515 cs:d5 miso:d19 mosi:d23 sck:d18 int:nada

#include <SPI.h>  // Library for using SPI Communication

#define CS_PIN 5  // Define the SPI CS pin as D5
// #define INT_PIN 33            // Define the interrupt pin as D21
#define SCK_PIN 18   // Define the SPI SCK pin as D18
#define MOSI_PIN 23  // Define the SPI MOSI pin as D23
#define MISO_PIN 19  // Define the SPI MISO pin as D19

void setup() {
    Serial.begin(9600);
    setOTA();
    setTouch();
    setScreen();
    SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, CS_PIN);
    setCAN();
}

void loop() {
    char valueStr[10];
    while (true) {
        ArduinoOTA.handle();
        snprintf(valueStr, sizeof(valueStr), pages[currentPage].format, sensorValue);
        printValue(valueStr, pages[currentPage].title, pages[currentPage].fontSize, pages[currentPage].posY,
                   pages[currentPage].verticalSwipe);
        if (gestureDetected) {
            // check if enough time has passed since last debounce
            if ((millis() - lastDebounceTime) > debounceDelay) {
                lastDebounceTime = millis();
                gestureDetected = false;
                uint8_t gesture = readGesture();

                if (gesture == 4) {  // swipe left
                    currentPage = (currentPage + 1) % (sizeof(pages) / sizeof(pages[0]));
                } else if (gesture == 3) {  // swipe right
                    currentPage =
                        (currentPage - 1 + sizeof(pages) / sizeof(pages[0])) % (sizeof(pages) / sizeof(pages[0]));
                } else if (gesture == 1 && pages[currentPage].verticalSwipe) {  // swipe up
                    struct can_frame frame;
                    frame.can_id = pages[currentPage].swipeUpId;
                    frame.can_dlc = 1;
                    frame.data[0] = 0x01;
                    mcp2515.sendMessage(&frame);
                } else if (gesture == 2 && pages[currentPage].verticalSwipe) {  // swipe down
                    struct can_frame frame;
                    frame.can_id = pages[currentPage].swipeDownId;
                    frame.can_dlc = 1;
                    frame.data[0] = 0x01;
                    mcp2515.sendMessage(&frame);
                }
            }
        }
        // delay(500);
    }
}