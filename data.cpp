#include "data.h"

int currentPage = 0;
unsigned long debounceDelay = 250;
unsigned long lastDebounceTime = 0;

// structure title-fontSize-posY-canId-canOffset-canType-canMultiplier-format
Page pages[] = {{"MAP", 60, 90, 0x520, 4, 2, 0.001, "%.3f"},
                {"BAT", 80, 80, 0x530, 0, 2, 0.01, "%.1f"},
                {"GEAR", 150, 50, 0x536, 0, 2, 1, "%d"},
                {"TPS", 80, 80, 0x520, 2, 2, 0.1, "%d"},
                {"COOLANT", 80, 80, 0x530, 6, 2, 0.1, "%d"},
                {"RPM", 60, 90, 0x520, 0, 2, 1, "%d"}};