#include "screen.h"

const int backgroundColor = TFT_BLACK;
const int valueColor = 0xFD20;
const int titleColor = TFT_CYAN;
const int arrowColor = TFT_GOLD;

TFT_eSPI tft = TFT_eSPI();
OpenFontRender render;

char lastValue[10] = "";
char lastTitle[11] = "";

void setScreen() {
    tft.init();
    render.loadFont(binaryttf, sizeof(binaryttf));
    render.setDrawer(tft);
    tft.setRotation(0);
    tft.fillScreen(backgroundColor);
}

void printValue(char *value, char *title, int fontSize, int posY, bool arrows) {
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
        tft.fillRect(0, 0, 240, 50, backgroundColor);
        tft.fillRect(0, 185, 240, 55, backgroundColor);
        tft.drawString(title, (tft.width() - tft.textWidth(title)) / 2, 190);
        strcpy(lastTitle, title);
        if (arrows) {
            tft.fillTriangle(110, 20, 130, 20, 120, 10, arrowColor);
            tft.fillTriangle(110, 30, 130, 30, 120, 40, arrowColor);
        }
    }
}