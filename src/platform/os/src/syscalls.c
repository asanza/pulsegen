/*
 * Copyright (c) 2019 Diego Asanza
 * 
 * SPDX-License-Identifier: Apache License 2.0
 * 
 * Created Date: Saturday April 6th 2019
 * Author: diego
 */

#include <stdlib.h>
#include <malloc.h>
#include <errno.h>

#include "newlib.h"
#include "FreeRTOS.h" // defines public interface we're implementing here
#if !defined(configUSE_NEWLIB_REENTRANT) ||  (configUSE_NEWLIB_REENTRANT!=1)
#error "configUSE_NEWLIB_REENTRANT must be set to 1 in FreeRTOSConfig.h"
#endif
#include "task.h"

extern char __HeapBase, __HeapLimit, HEAP_SIZE;
static int heap_avail = (int)&HEAP_SIZE;

char * sbrk(int incr) {
    static char *current_heap_ptr = &__HeapBase;

    vTaskSuspendAll();
    char *previous_heap_ptr = current_heap_ptr;
    if (current_heap_ptr + incr > &__HeapLimit) {
        #if( configUSE_MALLOC_FAILED_HOOK == 1 )
        {
            extern void vApplicationMallocFailedHook( void );
            vApplicationMallocFailedHook();
        }
        #else
        {
          _impure_ptr->_errno = ENOMEM; 
          xTaskResumeAll();
          return (char *)-1; // the malloc-family routine that called sbrk will return 0
        }
        #endif
    }
    current_heap_ptr += incr;
    heap_avail -= incr;
    xTaskResumeAll();
    return (char *) previous_heap_ptr;
}

char * _sbrk(int incr) { return sbrk(incr); };
void __malloc_lock(struct _reent *reent)
{
  (void) reent;
  vTaskSuspendAll();
};

void __malloc_unlock(struct _reent *reent)
{
  (void) reent;
  (void)xTaskResumeAll();
};

void __env_lock()    {       vTaskSuspendAll(); };
void __env_unlock()  { (void)xTaskResumeAll();  };

void *__wrap_malloc(size_t nbytes) {
    extern void * __real_malloc(size_t nbytes);
    void *p = __real_malloc(nbytes); // Solely for debug breakpoint...
    return p;
};

void *__wrap__malloc_r(void *reent, size_t nbytes) {
    extern void * __real__malloc_r(size_t nbytes);
    void *p = __real__malloc_r(nbytes); // Solely for debug breakpoint...
    return p;
};

void *pvPortMalloc( size_t xSize ) PRIVILEGED_FUNCTION {
    void *p = malloc(xSize);
    return p;
}
void vPortFree( void *pv ) PRIVILEGED_FUNCTION {
    free(pv);
};

size_t xPortGetFreeHeapSize( void ) PRIVILEGED_FUNCTION {
    struct mallinfo mi = mallinfo();
    return mi.fordblks + heap_avail;
}

void vPortInitialiseBlocks( void ) PRIVILEGED_FUNCTION {};