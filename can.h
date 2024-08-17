#ifndef CAN_H
#define CAN_H

#include <mcp2515.h>

#include "data.h"

extern MCP2515 mcp2515;
extern volatile float sensorValue;
extern void setCAN();
extern void send(int id, uint8_t data[], int length);

#endif