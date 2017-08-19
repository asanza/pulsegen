
#ifndef H_HAL_ERROR_
#define H_HAL_ERROR_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define HAL_ASSERT(x) if(!(x)) hal_error(__FILE__, __LINE__)

void hal_error(const char* file, int line);

#ifdef __cplusplus
}
#endif

#endif /* H_HAL_ERROR_ */
