#ifndef AURORA_CLIENT_MATRIX_H
#define AURORA_CLIENT_MATRIX_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


class LedMatrix {
private:
    Adafruit_NeoPixel matrix;

public:
    LedMatrix();

    void setColor(uint8_t width, uint8_t height, uint8_t red, uint8_t green, uint8_t blue);

    void setColor(uint16_t index, uint8_t red, uint8_t green, uint8_t blue);

    void clear();

    void begin();

    void redraw();

private:
    uint16_t calculateIndex(int8_t x, int8_t y);
};


#endif
