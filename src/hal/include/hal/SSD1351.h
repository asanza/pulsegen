#ifndef SSD1351_H_
#define SSD1351_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void disp_init( void );
void disp_pset(int16_t x, int16_t y, uint32_t color);
void disp_fillframe(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint32_t color);

#ifdef __cplusplus
}
#endif

#endif
