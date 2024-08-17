#include "can.h"

#define CS_PIN 5

MCP2515 mcp2515(CS_PIN);
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
        vTaskDelay(1);
    }
}

void setCAN() {
    mcp2515.reset();
    mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
    mcp2515.setNormalMode();
    xTaskCreate(canTask, "CAN Task", 4096, NULL, 1, NULL);
}
