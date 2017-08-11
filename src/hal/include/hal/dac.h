
#ifndef H_HAL_DAC_
#define H_HAL_DAC_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void dac_init(uint32_t val);
void dac_set( uint32_t val );

#ifdef __cplusplus
}
#endif

#endif /* H_HAL_GPIO_ */
