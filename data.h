#ifndef DATA_H
#define DATA_H

struct Page {
  char title[10];
  int fontSize;
  int posY;
  int canId;
  int canOffset;
  int canType;
  float canMultiplier;
  char format[5];
};

extern Page pages[6];
extern int currentPage;
extern unsigned long debounceDelay;
extern unsigned long lastDebounceTime;

#endif