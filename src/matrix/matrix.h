#ifndef AURORA_CLIENT_MATRIX_H
#define AURORA_CLIENT_MATRIX_H

#define MATRIX_LED_TYPE WS2812
#define MATRIX_PIN D8
#define N_ROW 16
#define N_COL 16
#define N_LEDS (N_COL * N_ROW)

#define FASTLED_ESP8266_RAW_PIN_ORDER

#include "FastLED.h"


class LedMatrix {
private:
    CRGB *leds = new CRGB[N_LEDS];

public:
    LedMatrix();

    void setColor(byte height, byte width, CRGB color);

    void setColor(byte index, CRGB color);

    void clear();

    static void redraw();

    CRGB *get() {
        return leds;
    }

private:
    static byte calculateIndex(byte height, byte width);
};


#endif
