#include "matrix.h"

LedMatrix::LedMatrix() {
    FastLED.addLeds<MATRIX_LED_TYPE, MATRIX_PIN, GRB>(leds, N_LEDS).setCorrection(TypicalLEDStrip);
}

void LedMatrix::setColor(byte height, byte width, CRGB color) {
    byte index = calculateIndex(height, width);

    this->leds[index] = color;
}


void LedMatrix::setColor(byte index, CRGB color) {
    this->leds[index] = color;
}

void LedMatrix::redraw() {
    FastLED.show();
    FastLED.show();
}

void LedMatrix::clear() {
    for (int i = 0; i < N_LEDS; i++) {
        if (leds[i].r > 0 || leds[i].g > 0 || leds[i].b > 0) {
            leds[i] = CRGB(0, 0, 0);
        }
    }
    redraw();
}

byte LedMatrix::calculateIndex(byte height, byte width) {
    byte startRowIdx = N_COL * height;
    byte isEven = height % 2;
    return isEven * (startRowIdx + (N_COL - width - 1)) + (1 - isEven) * (startRowIdx + width);;
}
