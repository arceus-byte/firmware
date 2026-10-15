
#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include "soc/soc_caps.h"
#include <stdint.h>

#define USER_SETUP_LOADED
#define ST7789_DRIVER
#define TFT_WIDTH 135
#define TFT_HEIGHT 240
#define CGRAM_OFFSET

#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS 15
#define TFT_DC 2
#define TFT_RST 4
#define TFT_BL 32
#define TFT_BACKLIGHT_ON HIGH

#define SPI_FREQUENCY 20000000
#define SPI_READ_FREQUENCY 6000000
#define SMOOTH_FONT 1

#define HAS_SCREEN
#define ROTATION 1
#define MINBRIGHT (uint8_t)1

#define FP 1
#define FM 2
#define FG 3

#define BTN_ALIAS "\"BOOT\""
#define BTN_ACT LOW
#define BOOT_BTN 0

#define SPI_SS_PIN 5
#define SPI_MOSI_PIN 23
#define SPI_MISO_PIN 19
#define SPI_SCK_PIN 18

static const uint8_t SS = SPI_SS_PIN;
static const uint8_t MOSI = SPI_MOSI_PIN;
static const uint8_t MISO = SPI_MISO_PIN;
static const uint8_t SCK = SPI_SCK_PIN;

#define GROVE_SDA 21
#define GROVE_SCL 22

static const uint8_t SDA = GROVE_SDA;
static const uint8_t SCL = GROVE_SCL;

#define SDCARD_CS -1
#define SDCARD_SCK SPI_SCK_PIN
#define SDCARD_MISO SPI_MISO_PIN
#define SDCARD_MOSI SPI_MOSI_PIN

#define TXLED -1
#define RXLED -1

#define LED_ON HIGH
#define LED_OFF LOW

#endif
