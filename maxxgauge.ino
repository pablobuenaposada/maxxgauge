#include <SPI.h>  // Library for using SPI Communication

#include "can.h"
#include "data.h"
#include "ota.h"
#include "screen.h"
#include "touch.h"

#define CS_PIN 5     // Define the SPI CS pin as D5
#define SCK_PIN 18   // Define the SPI SCK pin as D18
#define MOSI_PIN 23  // Define the SPI MOSI pin as D23
#define MISO_PIN 19  // Define the SPI MISO pin as D19

// SCHEMATICS
// 12v to 5v adapter: 5v->vin gnd->gnd
// Screen waveshare 1.28" 240x240 touch lcd: vcc->3v3 gnd->gnd mosi->d13 sclk->d14 cs->d4 dc->d32 bl->3v3 sda->d21
// scl->d22 int->d25
// CAN bus shield MCP2515: vcc->vin gnd->gnd cs->d5 so->d19 si->d23 sck->d18

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
        if (canError) {
            noConnection();
        } else {
            if (pages[currentPage].isInteger) {
                const char* translatedValue = translate(sensorValue, pages[currentPage].translation);
                sprintf(valueStr, "%s", translatedValue);
            } else {
                snprintf(valueStr, sizeof(valueStr), pages[currentPage].format, sensorValue);
            }
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
                        uint8_t data[] = {0x01};
                        send(pages[currentPage].swipeUpId, data, 1);
                        data[0] = 0x00;
                        delay(500);
                        send(pages[currentPage].swipeUpId, data, 1);
                    } else if (gesture == 2 && pages[currentPage].verticalSwipe) {  // swipe down
                        uint8_t data[] = {0x01};
                        send(pages[currentPage].swipeDownId, data, 1);
                        data[0] = 0x00;
                        delay(500);
                        send(pages[currentPage].swipeDownId, data, 1);
                    }
                }
            }
        }
    }
}