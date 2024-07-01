#include "touch.h"
#include "screen.h"
#include "data.h"
//creo que estoy usando vspi
//pantalla tft_miso:nada tft_mosi:d13 tft_sclk:d14 tft_cs:d4 tft_dc:d32 tft_rst:nada tft_bl:3v touch_sda:d21 touch_scl:d22 touch_int:d25 touch_rst:nada
//mcp2515 cs:d5 miso:d19 mosi:d23 sck:d18 int:nada 

#include <SPI.h>              // Library for using SPI Communication 
#include <mcp2515.h>          // Library for using CAN Communication (https://github.com/autowp/arduino-mcp2515/)

#define CS_PIN 5              // Define the SPI CS pin as D5
//#define INT_PIN 33            // Define the interrupt pin as D21
#define SCK_PIN 18            // Define the SPI SCK pin as D18
#define MOSI_PIN 23           // Define the SPI MOSI pin as D23
#define MISO_PIN 19           // Define the SPI MISO pin as D19

MCP2515 mcp2515(CS_PIN);          // SPI CS Pin 10
volatile float sensorValue = 0.0;

void canTask(void *pvParameters) {
  struct can_frame canMsg;
  while (true) {
    if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
      if (canMsg.can_id == pages[currentPage].canId) {
        int rawValue = 0;
        for (int i = 0; i < pages[currentPage].canType; ++i) {
            rawValue |= (canMsg.data[pages[currentPage].canOffset + i] << (8 * i));
        }
        sensorValue = rawValue * pages[currentPage].canMultiplier;
      }
    }
  }
}

void setup() {
  setTouch();
  setScreen();
  Serial.begin(9600);

  SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, CS_PIN);  // Initialize SPI bus with custom pins
  //pinMode(INT_PIN, INPUT);

  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ); // Set CAN speed to 500KBPS and Clock to 8MHz
  mcp2515.setNormalMode();                  // Set CAN to normal mode

  xTaskCreate(canTask, "CAN Task", 4096, NULL, 1, NULL);

}

void loop() {
  char valueStr[10];
  while (true) {
    snprintf(valueStr, sizeof(valueStr), pages[currentPage].format, sensorValue);
    printValue(valueStr, pages[currentPage].title, pages[currentPage].fontSize, pages[currentPage].posY);
    if (gestureDetected) {
      // check if enough time has passed since last debounce
      if ((millis() - lastDebounceTime) > debounceDelay) {
        lastDebounceTime = millis();
        gestureDetected = false;
        uint8_t gesture = readGesture();
        
        if (gesture == 4) { // swipe left
          currentPage = (currentPage + 1) % (sizeof(pages) / sizeof(pages[0]));
        }
        else if (gesture == 3) { // swipe right
          currentPage = (currentPage - 1 + sizeof(pages) / sizeof(pages[0])) % (sizeof(pages) / sizeof(pages[0]));
        }
      }
    }
    //delay(500);
  }
}