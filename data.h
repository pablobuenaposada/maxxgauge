#ifndef DATA_H
#define DATA_H

struct Page {
    char title[11];
    int fontSize;
    int posY;
    int canId;
    int canOffset;
    int canType;
    float canMultiplier;
    bool isInteger;
    char format[5];
    bool verticalSwipe;
    int swipeUpId;
    int swipeDownId;
};

extern Page pages[8];
extern int currentPage;
extern unsigned long debounceDelay;
extern unsigned long lastDebounceTime;

#endif