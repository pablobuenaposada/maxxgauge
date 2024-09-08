#include "can.h"

#include <Arduino.h>

#define CS_PIN 5
#define CAN_TIMEOUT 1000

MCP2515 mcp2515(CS_PIN);
volatile float sensorValue = 0;
volatile bool canError = false;

void canTask(void *pvParameters) {
    struct can_frame canMsg;
    unsigned long lastCanMessageTime = millis();

    while (true) {
        if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
            canError = false;
            lastCanMessageTime = millis();

            if (canMsg.can_id == pages[currentPage].canId) {
                int rawValue = 0;
                for (int i = 0; i < pages[currentPage].canType; ++i) {
                    rawValue |= (canMsg.data[pages[currentPage].canOffset + i] << (8 * i));
                }
                sensorValue = rawValue * pages[currentPage].canMultiplier;
            }
        }

        // Check for CAN bus inactivity
        if (millis() - lastCanMessageTime > CAN_TIMEOUT) {
            canError = true;
        }
        vTaskDelay(1);
    }
}

void setCAN() {
    mcp2515.reset();
    mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
    mcp2515.setNormalMode();
    xTaskCreate(canTask, "CAN Task", 4096, NULL, 1, NULL);
}

void send(int id, uint8_t data[], int length) {
    struct can_frame frame;
    frame.can_id = id;
    frame.can_dlc = length;
    for (int i = 0; i < length; i++) {
        frame.data[i] = data[i];
    }
    mcp2515.sendMessage(&frame);
}
