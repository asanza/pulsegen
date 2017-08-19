#include <hal/error.h>

void hal_error(const char* file, int line){
    asm("BKPT");
}
