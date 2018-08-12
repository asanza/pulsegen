/*
 * pulsegen
 * Copyright (C) 2018  Diego Asanza <f.asanza@gmail.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UI_H
#define UI_H

#include "sys/evt.h"
#include <pulsegen/systate.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /* initialize the ui*/
    void ui_init(struct system_state *state);

    /* call regularly from your main loop */
    void ui_update(void);

    /* call each 10ms */
    void ui_timming_tasks(void);

#ifdef __cplusplus
}
#endif

#endif /* UI_H */
