#include "data.h"

#include <cstddef>

int currentPage = 0;
unsigned long debounceDelay = 250;
unsigned long lastDebounceTime = 0;

// structure
// title-fontSize-posY-canId-canOffset-canType-canMultiplier-isInteger-format-verticalSwipe-swipeUpId-swipeDownId
Page pages[] = {{"GEAR", 150, 50, 0x536, 0, 2, 1, true, "%d", false, NULL, NULL},
                {"MAP", 60, 90, 0x520, 4, 2, 0.001, false, "%.3f", false, NULL, NULL},
                {"BAT", 80, 80, 0x530, 0, 2, 0.01, false, "%.1f", false, NULL, NULL},
                {"TPS", 80, 80, 0x520, 2, 2, 0.1, true, "%d", false, NULL, NULL},
                {"COOLANT", 80, 80, 0x530, 6, 2, 0.1, true, "%d", false, NULL, NULL},
                {"RPM", 60, 90, 0x520, 0, 2, 1, true, "%d", false, NULL, NULL},
                {"DCT MODE", 80, 80, 0x107, 2, 2, 1, true, "%d", true, 0x100, 0x101},
                {"DRIVELOGIC", 80, 80, 0x107, 0, 2, 1, true, "%d", true, 0x102, 0x103}};