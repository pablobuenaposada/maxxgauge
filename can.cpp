#include "can.h"

#define CS_PIN 5  // Define the SPI CS pin as D5

MCP2515 mcp2515(CS_PIN);  // SPI CS Pin 10

void setCAN() {
    mcp2515.reset();
    mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
    mcp2515.setNormalMode();
}