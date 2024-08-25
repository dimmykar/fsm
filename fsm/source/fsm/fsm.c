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

fsmr_t fsm_init(fsm_t *fsm, fsm_state_t *initial_state, fsm_state_t **states_list, void *setup_data) {
    if (fsm == NULL || initial_state == NULL || states_list == NULL) {
        return fsmERRPAR;
    }

    memset(fsm, 0x00, sizeof(*fsm));
    fsm->states_list = states_list;

    if (setup_data != NULL) {
        fsm_state_t *state = *fsm->states_list;
        while (state != NULL) {
            fsmr_t res = state->ops.setup(state, setup_data);
            if (res != fsmOK) {
                return res;
            }
            ++state;
        }
    }

    fsm->curr_state = fsm->prev_state = fsm->next_state = initial_state;
    return fsmOK;
}

fsmr_t fsm_run(fsm_t *fsm) {
    if (fsm == NULL) {
        return fsmERRPAR;
    }

    return fsmOK;
}

fsmr_t fsm_state_transition(fsm_t *fsm, uint32_t new_state_id) {
    if (fsm == NULL) {
        return fsmERRPAR;
    }

    return fsmOK;
}
