
#ifndef H_HAL_KEYBD_
#define H_HAL_KEYBD_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

enum key_type{
    KEY_TA1,
    KEY_TA2,
    KEY_TA3,
    KEY_TA4,
    KEY_TA5,
    KEY_POW,
    ENC_INC,
    ENC_DEC
};

typedef void (*key_handler_t)(enum key_type);

void keybd_init(key_handler_t fn);

#ifdef __cplusplus
}
#endif

#endif /* H_HAL_KEYBD_ */
