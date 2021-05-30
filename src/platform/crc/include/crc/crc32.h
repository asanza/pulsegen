#ifndef SRC_PLATFORM_LIB_MATH_INCLUDE_MATH_CRC32_H
#define SRC_PLATFORM_LIB_MATH_INCLUDE_MATH_CRC32_H

#ifdef __cplusplus
extern "C"  {
#endif

#include <stdint.h>
#include <stddef.h>

uint32_t crc32(uint32_t crc, const void *buf, size_t size);

#ifdef __cplusplus
}
#endif
#endif /* SRC_PLATFORM_LIB_MATH_INCLUDE_MATH_CRC32_H */
