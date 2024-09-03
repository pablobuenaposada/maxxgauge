#include "data.h"

#include <cstddef>
#include <map>

int currentPage = 0;
unsigned long debounceDelay = 250;
unsigned long lastDebounceTime = 0;

// translations
std::map<int, String> gearTranslations = {{0, "N"}, {-2, "R"}};
std::map<int, String> dctModeTranslations = {{0, "AUTO"}, {1, "MANUAL"}};

// structure
// title-fontSize-posY-canId-canOffset-canType-canMultiplier-format-verticalSwipe-swipeUpId-swipeDownId
Page pages[] = {{"MAP", 60, 90, 0x520, 4, 2, 0.001, "%.3f", false, NULL, NULL, {}},
                {"BAT", 80, 80, 0x530, 0, 2, 0.01, "%.1f", false, NULL, NULL, {}},
                {"GEAR", 150, 50, 0x536, 0, 2, 1, "%d", false, NULL, NULL, gearTranslations},
                {"TPS", 80, 80, 0x520, 2, 2, 0.1, "%d", false, NULL, NULL, {}},
                {"COOLANT", 80, 80, 0x530, 6, 2, 0.1, "%d", false, NULL, NULL, {}},
                {"RPM", 60, 90, 0x520, 0, 2, 1, "%d", false, NULL, NULL, {}},
                {"DCT MODE", 80, 80, 0x530, 0, 2, 0.01, "%.1f", true, 0x100, 0x101, dctModeTranslations},
                {"DRIVELOGIC", 80, 80, 0x530, 0, 2, 0.01, "%.1f", true, 0x102, 0x103, {}}};