#include "command.h"

void setBrightness(LedMatrix* matrix, byte value){
    matrix->setBrightness(value);
    matrix->redraw();
}
