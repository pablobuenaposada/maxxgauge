#ifndef SCREEN_H
#define SCREEN_H

#include <TFT_eSPI.h>
#include "OpenFontRender.h"
#include "binaryttf.h"

void setScreen();
void printValue(char *value, char *title, int fontSize, int posY);

#endif