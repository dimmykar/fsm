/**
 * \file            fsm.c
 * \brief           Finite State Machine
 */

/*
 * Copyright (c) 2024 Dmitry KARASEV
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This file is part of FSM - Finite State Machine library for small and embedded devices.
 *
 * Authors:         Dmitry KARASEV <karasevsdmitry@yandex.ru>
 * Version:         ${version}
 */

#include "fsm/fsm.h"

#include <string.h>

fsmr_t fsm_init(fsm_t *fsm, const fsm_init_params_t *params) {
    if (fsm == NULL || params == NULL || params->initial_state == NULL ||
        params->states_list == NULL) {
        return fsmERRPAR;
    }

    memset(fsm, 0x00, sizeof(*fsm));
    fsm->states_list = params->states_list;

    if (params->setup_data != NULL) {
        fsm_state_t *state = *fsm->states_list;
        while (state != NULL) {
            fsmr_t res = state->ops.setup(state, params->setup_data);
            if (res != fsmOK) {
                return res;
            }
            ++state;
        }
    }

#if FSM_CFG_OS
    if (!fsm_sys_mutex_create(&fsm->lock)) {
        return fsmERR;
    }
#endif /* FSM_CFG_OS */

    fsm->curr_state = fsm->prev_state = fsm->next_state = params->initial_state;
    return fsmOK;
}

fsmr_t fsm_run(fsm_t *fsm) {
    if (fsm == NULL) {
        return fsmERRPAR;
    }

    fsmr_t result = fsmOK;

#if FSM_CFG_OS
    fsm_sys_mutex_wait(&fsm->lock);
#endif /* FSM_CFG_OS */
    if (fsm->curr_state != fsm->next_state) {
        fsm->prev_state = fsm->curr_state;
        fsm->curr_state = fsm->next_state;
#if FSM_CFG_OS
        fsm_sys_mutex_release(&fsm->lock);
#endif /* FSM_CFG_OS */

        if (fsm->prev_state->ops.exit != NULL) {
            result |= fsm->prev_state->ops.exit(fsm->prev_state);
        }
        if (fsm->curr_state->ops.enter != NULL) {
            result |= fsm->curr_state->ops.enter(fsm->curr_state);
        }
    } else {
#if FSM_CFG_OS
        fsm_sys_mutex_release(&fsm->lock);
#endif /* FSM_CFG_OS */
    }

    result |= fsm->curr_state->ops.run(fsm->curr_state);

    return result;
}

fsmr_t fsm_state_transition(fsm_t *fsm, uint32_t new_state_id) {
    if (fsm == NULL || fsm->states_list == NULL) {
        return fsmERRPAR;
    }

    for (size_t i = 0; fsm->states_list[i] != NULL; i++) {
        fsm_state_t *state = fsm->states_list[i];

        if (state->id == new_state_id) {
#if FSM_CFG_OS
            fsm_sys_mutex_wait(&fsm->lock);
#endif /* FSM_CFG_OS */
            if (fsm->curr_state != state) {
                fsm->next_state = state;
            }
#if FSM_CFG_OS
            fsm_sys_mutex_release(&fsm->lock);
#endif /* FSM_CFG_OS */
            return fsmOK;
        }
    }

    return fsmERR;
}
