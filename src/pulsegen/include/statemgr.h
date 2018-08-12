#ifndef STATEMGR_H
#define STATEMGR_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "systate.h"

    void state_init(struct system_state *state);
    void state_update(struct system_state *state, enum system_event evt, void *args);

#ifdef __cplusplus
}
#endif

#endif /* STATEMGR_H */
