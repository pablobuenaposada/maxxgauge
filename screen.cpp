#include "screen.h"

const int backgroundColor = TFT_BLACK;
const int valueColor = 0xFD20;
const int titleColor = TFT_CYAN;
const int arrowColor = TFT_GOLD;

TFT_eSPI tft = TFT_eSPI();
OpenFontRender render;

char lastValue[10] = "";
char lastTitle[11] = "";
char lastNoConnection = false;

void setScreen() {
    tft.init();
    render.loadFont(binaryttf, sizeof(binaryttf));
    render.setDrawer(tft);
    tft.setRotation(0);
    tft.fillScreen(backgroundColor);
}

void noConnection() {
    if (!lastNoConnection) {
        tft.fillRect(0, 0, 240, 240, backgroundColor);
        render.setFontColor(TFT_RED);
        render.setFontSize(25);
        render.setCursor(tft.width() / 2, 90);
        render.cprintf("NO CANBUS");
        render.setCursor(tft.width() / 2, 130);
        render.cprintf("CONNECTION");
        lastNoConnection = true;
        strcpy(lastValue, "");
        strcpy(lastTitle, "");
    }
}

const char* translate(float value, const std::map<int, String>& translation) {
    int intValue = static_cast<int>(value);

    auto it = translation.find(intValue);
    if (it != translation.end()) {
        return it->second.c_str();
    } else {
        
    }
}

void printValue(char *value, char *title, int fontSize, int posY, bool arrows) {
    lastNoConnection = false;
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