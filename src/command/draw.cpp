#include "command.h"

#define RGB_COLORS_COUNT 3
#define MAX_RECEIVE_MATRIX_WIDTH 16
#define META_INFO_SIZE 1

void draw(LedMatrix* matrix, byte* payload, int length) {
    byte tmpMod;
    byte oneCellRGB[RGB_COLORS_COUNT];
    int height = 0, width = 0;
    // Первый байт - системный. Поэтому его пропускаем
    payload++;

    for (int receivedByteIndex = 0; receivedByteIndex < length - META_INFO_SIZE; receivedByteIndex++) {
        tmpMod = receivedByteIndex % 3;
        if (receivedByteIndex > 0 && tmpMod == 0) {
            matrix->setColor(height, width, oneCellRGB[0], oneCellRGB[1], oneCellRGB[2]);
            width ++;
            if (width == MAX_RECEIVE_MATRIX_WIDTH)
            {
              height ++;
              width = 0;
            }
        }
        oneCellRGB[tmpMod] = payload[receivedByteIndex];
    }

    matrix->setColor(height, width, oneCellRGB[0], oneCellRGB[1], oneCellRGB[2]);
    matrix->redraw();
}
