#ifndef COMMAND_H
#define COMMAND_H
#include "matrix/matrix.h"

#define DRAW_COMMAND 1
#define BRIGHTNESS_COMMAND 2

/*
 * @brief Команда отрисовки картинки на матрице
 *
 * Итерируясь по набору байтов сериализует их в цвет. Каждая группа из 
 * 3 байтов считается за RGB цвет. При сериализации цвета устанавливает
 * цвет для текущей ячейки. 
 * После этого текущая просматриваемая ячейка изменяется (на следующую по горизонтали). 
 * Заполнение идет построчно-итеративно
 * Только при заполнении одной строки начинается заполнение следующей
 */
void draw(LedMatrix* matrix, byte *payload, int length);

/*
 * @brief Установить яркость матрицы
 *
 * Яркость устанавливается в пределах [0; 255]
 */
void setBrightness(LedMatrix* matrix, byte value);

#endif // COMMAND_H

