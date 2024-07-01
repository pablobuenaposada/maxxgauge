//------------------- User_Setup.h -------------------

#define GC9A01_DRIVER

// Define the pins used to connect to the display
#define TFT_CS 4  // Chip select control pin
#define TFT_DC 32 // Data Command control pin
//#define TFT_RST 5  // Reset pin
#define TFT_MOSI 13 // Data out
#define TFT_SCLK 14 // Clock out

// #define TFT_BL   21  // Optional backlight control pin
// #define TFT_BACKLIGHT_ON HIGH // Level to turn ON backlight (HIGH or LOW)

#define SPI_FREQUENCY 27000000 // Change this value if you have trouble with display

#define LOAD_FONT2
#define LOAD_FONT7
