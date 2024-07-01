#ifndef TOUCH_H
#define TOUCH_H

#include <Arduino.h>
#include <Wire.h>

extern volatile bool gestureDetected;

void setTouch();
uint8_t readGesture();

#endif