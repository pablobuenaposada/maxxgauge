#include "screen.h"

const int backgroundColor = TFT_BLACK;
const int valueColor = 0xFD20;
const int titleColor = TFT_CYAN;

TFT_eSPI tft = TFT_eSPI();
OpenFontRender render;

char lastValue[10] = "";
char lastTitle[10] = "";

void setScreen(){
  tft.init();
  render.loadFont(binaryttf, sizeof(binaryttf));
  render.setDrawer(tft);
  tft.setRotation(0);
  tft.fillScreen(backgroundColor);
}

void printValue(char *value, char *title, int fontSize, int posY) {
  if (strcmp(value, lastValue) != 0) {
    render.setFontColor(valueColor);
    render.setFontSize(fontSize);
    render.setCursor(tft.width() / 2, posY);
    tft.fillRect(0, 40, 240, 145, backgroundColor);
    render.cprintf(value);
    strcpy(lastValue, value);
  }

  if (strcmp(title, lastTitle) != 0) {
    tft.setTextColor(titleColor);
    tft.setTextFont(2);
    tft.setTextSize(2);
    tft.fillRect(0, 185, 240, 55, backgroundColor);
    tft.drawString(title, (tft.width() - tft.textWidth(title)) / 2, 190);
    strcpy(lastTitle, title);
  }
}