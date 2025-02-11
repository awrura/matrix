#include "matrix.h"

//                     THANK YOU
// -------------------------------------------------------------
// The matrix configuration was taken from the                  |
// MatrixOS project (by AlexGyver)                              |
// see more details here https://alexgyver.ru/matrix_guide/     |
// -------------------------------------------------------------

constexpr uint8_t WIDTH = 16;              // ширина матрицы
constexpr uint8_t HEIGHT = 16;             // высота матрицы
constexpr uint8_t PIN = D8;
constexpr uint16_t NUM_PIXELS = WIDTH * HEIGHT;

constexpr uint8_t SEGMENTS = 1;            // диодов в одном "пикселе"
constexpr uint8_t MATRIX_TYPE = 0;         // тип матрицы: 0 - зигзаг, 1 - последовательная
constexpr uint8_t CONNECTION_ANGLE = 0;    // угол подключения: 0 - левый нижний, 1 - левый верхний, 2 - правый верхний, 3 - правый нижний
constexpr uint8_t STRIP_DIRECTION = 1;     // направление ленты: 0 - вправо, 1 - вверх, 2 - влево, 3 - вниз

constexpr uint8_t calc_width(uint8_t connectionAngle, uint8_t stripDirection) {
    return ((connectionAngle == 0 || connectionAngle == 3) && stripDirection % 2 == 0) ||
           ((connectionAngle == 1 || connectionAngle == 2) && stripDirection % 2 != 0) ? WIDTH : HEIGHT;
}

constexpr uint8_t NORMALIZED_WIDTH = calc_width(CONNECTION_ANGLE, STRIP_DIRECTION);

constexpr int16_t calc_this_x(int16_t x, int16_t y) {
    switch (CONNECTION_ANGLE) {
        case 0: 
            return (STRIP_DIRECTION == 1) ? y : x;
        case 1: 
            return (STRIP_DIRECTION == 3) ? (HEIGHT - y - 1) : x;
        case 2: 
            return (STRIP_DIRECTION == 2) ? (WIDTH - x - 1) : (HEIGHT - y - 1);
        case 3: 
            return (STRIP_DIRECTION == 1) ? y : (WIDTH - x - 1);
        default: 
            return x;
    }
}

constexpr int16_t calc_this_y(int16_t x, int16_t y) {
    switch (CONNECTION_ANGLE) {
        case 0: 
            return (STRIP_DIRECTION == 1) ? x : y;
        case 1: 
            return (STRIP_DIRECTION == 3) ? x : (HEIGHT - y - 1);
        case 2: 
            return (STRIP_DIRECTION == 2) ? y : (WIDTH - x - 1);
        case 3: 
            return (STRIP_DIRECTION == 1) ? (WIDTH - x - 1) : y;
        default: 
            return y;
    }
}

LedMatrix::LedMatrix(): matrix(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800) {}

void LedMatrix::begin() {
    matrix.begin();
}

void LedMatrix::setColor(uint8_t width, uint8_t height, uint8_t red, uint8_t green, uint8_t blue) {
    uint16_t index = calculateIndex(width, height);
    this->setColor(index, red, green, blue);
}

void LedMatrix::setColor(uint16_t index, uint8_t red, uint8_t green, uint8_t blue) {
    matrix.setPixelColor(index, red, green, blue);
}

void LedMatrix::redraw() {
    matrix.show();
}

void LedMatrix::clear() {
    matrix.clear();
    this->redraw();
}

uint16_t LedMatrix::calculateIndex(int8_t x, int8_t y) {
    int16_t norm_x = calc_this_x(x, y);
    int16_t norm_y = calc_this_y(x, y);

    if ((norm_y % 2 == 0) || MATRIX_TYPE) {
      return (norm_y * NORMALIZED_WIDTH + norm_x);
    } else {
      return (norm_y * NORMALIZED_WIDTH + NORMALIZED_WIDTH - norm_x - 1);
    }
}
