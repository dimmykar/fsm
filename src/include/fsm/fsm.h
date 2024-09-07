/**
 * \file            fsm.h
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

#ifndef FSM_HDR_H
#define FSM_HDR_H

#include <stdint.h>
#include <stddef.h>

#include "fsm/fsm_config.h"
#include "fsm/system/fsm_sys.h"

typedef struct fsm_state fsm_state_t;

/**
 * \brief           FSM result enumeration
 */
typedef enum fsmr {
    fsmOK = 0x00,                            /*!< Everything OK */
    fsmERR = 0x01,                           /*!< Common error */
    fsmERRPAR = 0x02,                        /*!< Parameter error */
} fsmr_t;

/**
 * \brief           FSM State specific operations
 */
typedef struct fsm_state_ops {
    /**
     * \brief      Pass user specific data to state
     * \details    Called once on FSM initialization
     * \param[in]  state: Pointer to state
     * \param[in]  data: Pointer to user specific data passed on FSM initialization.
     *                 May be NULL
     */
    fsmr_t (*setup)(fsm_state_t *state, void *data);

    /**
     * \brief      Enter state handler
     * \details    Called once on entering to state
     * \param[in]  state: Pointer to state
     * \return     \ref fsmOK on success, member of \ref fsmr_t otherwise
     */
    fsmr_t (*enter)(fsm_state_t *state);

    /**
     * \brief      Exit state handler
     * \details    Called once on exiting from state
     * \param[in]  state: Pointer to state
     * \return     \ref fsmOK on success, member of \ref fsmr_t otherwise
     */
    fsmr_t (*exit)(fsm_state_t *state);

    /**
     * \brief      State main body handler
     * \details    Called periodically until state changes
     * \param[in]  state: Pointer to state
     * \return     \ref fsmOK on success, member of \ref fsmr_t otherwise
     */
    fsmr_t (*run)(fsm_state_t *state);
} fsm_state_ops_t;

/**
 * \brief           FSM State handle
 */
typedef struct fsm_state {
    uint32_t id;                             /*!< State unique numeric ID */
    fsm_state_ops_t ops;                     /*!< State specific operations */
    void *data;                              /*!< User defined state data */
} fsm_state_t;

/**
 * \brief           The parameters passed on FSM initialization
 */
typedef struct fsm_init_params {
    fsm_state_t *initial_state;              /*!< FSM initial state */
    fsm_state_t **states_list;               /*!< Pointer to array with all FSM states.
                                                      Must be ended with NULL record */
    void *setup_data;                        /*!< Pointer to user defined data passed to
                                                      all states on initialization. May be NULL */
} fsm_init_params_t;

/**
 * \brief           FSM handle
 */
typedef struct fsm {
    fsm_state_t **states_list;               /*!< All available states in FSM. Must be ended with NULL record */
    fsm_state_t *curr_state;                 /*!< FSM current state */
    fsm_state_t *prev_state;                 /*!< FSM previous state */
    fsm_state_t *next_state;                 /*!< FSM next state */

#if FSM_CFG_OS && !__DOXYGEN__
    FSM_CFG_OS_MUTEX_HANDLE lock;            /*!< FSM safe guard locker object based on mutex */
#endif /* FSM_CFG_OS && !__DOXYGEN__ */
} fsm_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \brief           Initialize finite state machine
 * \param[in]       fsm: FSM instance
 * \param[in]       params: Pointer to init parameters
 * \return          \ref fsmOK on success, member of \ref fsmr_t otherwise
 */
fsmr_t fsm_init(fsm_t *fsm, const fsm_init_params_t *params);

/**
 * \brief           FSM Main Loop
 * \details         Performs new state transition if needed and current state run
 * \param[in]       fsm: FSM instance
 *                  \ref fsmOK on success, member of \ref fsmr_t otherwise
 */
fsmr_t fsm_run(fsm_t *fsm);

/**
 * \brief           Set transition to next state in FSM
 * \details         New state transition will perform on next FSM Main Loop cycle
 *                      if new state is set successfully as next FSM state
 * \param[in]       fsm: FSM instance
 * \param[in]       new_state_id: Unique numeric ID of the new state to go to
 * \return          \ref fsmOK if the new state is the same as the current or
 *                      the new state is set as FSM next state, member of \ref fsmr_t otherwise
 */
fsmr_t fsm_state_transition(fsm_t *fsm, uint32_t new_state_id);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* FSM_HDR_H */
