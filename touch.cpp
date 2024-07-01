#include "touch.h"

//#define TOUCH_RST_PIN 26
#define TOUCH_SDA_PIN 21
#define TOUCH_SCL_PIN 22
#define TOUCH_INT_PIN 25
#define CST816S_ADDR 0x15
#define REG_GESTURE_ID 0x01

volatile bool gestureDetected = false;

void IRAM_ATTR handleTouchInterrupt() {
  gestureDetected = true;
}

void resetSensor() {
  //pinMode(TOUCH_RST_PIN, OUTPUT);
  //digitalWrite(TOUCH_RST_PIN, LOW);
  delay(100);
  //digitalWrite(TOUCH_RST_PIN, HIGH);
  delay(100);
}

void setTouch(){
  Wire.begin(TOUCH_SDA_PIN, TOUCH_SCL_PIN);
  pinMode(TOUCH_INT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(TOUCH_INT_PIN), handleTouchInterrupt, FALLING);
  resetSensor();
}

uint8_t readGesture() {
  Wire.beginTransmission(CST816S_ADDR);
  Wire.write(REG_GESTURE_ID);
  Wire.endTransmission();
  Wire.requestFrom(CST816S_ADDR, 1);

  if (Wire.available()) {
    return Wire.read();
  }
  return 0x00;
}