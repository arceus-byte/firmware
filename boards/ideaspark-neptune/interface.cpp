
#include <Arduino.h>
#include <globals.h>
#include <interface.h>
#include "core/powerSave.h"

static bool nextPending = false;
static bool selectPending = false;
static bool backPending = false;

static bool buttonDown = false;
static bool longPressHandled = false;
static unsigned long pressStart = 0;
static unsigned long lastRelease = 0;
static unsigned long lastChange = 0;
static int clickCount = 0;

void _setup_gpio() {
    pinMode(BOOT_BTN, INPUT_PULLUP);
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
    Serial.begin(115200);
}

void _setBrightness(uint8_t brightval) {
    uint32_t duty = map(constrain(brightval, 0, 100), 0, 100, 0, 255);
    analogWrite(TFT_BL, duty);
}

void InputHandler(void) {
    const unsigned long now = millis();
    const bool pressed = digitalRead(BOOT_BTN) == LOW;

    if (pressed != buttonDown && now - lastChange >= 35) {
        lastChange = now;
        buttonDown = pressed;

        if (pressed) {
            pressStart = now;
            longPressHandled = false;
        } else if (!longPressHandled) {
            clickCount++;
            lastRelease = now;
        }
    }

    if (buttonDown && !longPressHandled &&
        now - pressStart >= 750) {
        backPending = true;
        longPressHandled = true;
        clickCount = 0;
    }

    if (!buttonDown && clickCount > 0 &&
        now - lastRelease >= 300) {
        if (clickCount >= 2) {
            selectPending = true;
        } else {
            nextPending = true;
        }
        clickCount = 0;
    }

    if (nextPending || selectPending || backPending) {
        if (wakeUpScreen()) {
            nextPending = false;
            selectPending = false;
            backPending = false;
            return;
        }

        NextPress = nextPending;
        SelPress = selectPending;
        EscPress = backPending;
        PrevPress = false;
        AnyKeyPress = true;

        nextPending = false;
        selectPending = false;
        backPending = false;
    }
}

void powerOff() {
    tft.fillScreen(TFT_BLACK);
    digitalWrite(TFT_BL, LOW);
    esp_sleep_enable_ext0_wakeup((gpio_num_t)BOOT_BTN, 0);
    esp_deep_sleep_start();
}
