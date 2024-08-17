#ifndef CAN_H
#define CAN_H

#include <mcp2515.h>

#include "data.h"

extern MCP2515 mcp2515;
extern volatile float sensorValue;
extern void setCAN();

#endif