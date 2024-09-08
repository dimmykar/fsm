/**
 * \file            fsm_sys.h
 * \brief           FSM OS abstraction interface
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
 * Version:         0.1.0
 */

#ifndef FSM_SYS_HDR_H
#define FSM_SYS_HDR_H

#include <stddef.h>
#include <stdint.h>

#include "fsm/fsm_config.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if FSM_CFG_OS || __DOXYGEN__

/**
 * \defgroup        FSM_SYS System functions
 * \brief           System functions when used with operating system
 * \{
 */

/**
 * \brief           Create a new mutex and assign value to handle
 * \param[out]      mutex: Output variable to save mutex handle
 * \return          `1` on success, `0` otherwise
 */
uint8_t fsm_sys_mutex_create(FSM_CFG_OS_MUTEX_HANDLE *mutex);

/**
 * \brief           Wait for a mutex until ready (unlimited time)
 * \param[in]       mutex: Mutex handle to wait for
 * \return          `1` on success, `0` otherwise
 */
uint8_t fsm_sys_mutex_wait(FSM_CFG_OS_MUTEX_HANDLE *mutex);

/**
 * \brief           Release already locked mutex
 * \param[in]       mutex: Mutex handle to release
 * \return          `1` on success, `0` otherwise
 */
uint8_t fsm_sys_mutex_release(FSM_CFG_OS_MUTEX_HANDLE *mutex);

/**
 * \}
 */

#endif /* FSM_CFG_OS || __DOXYGEN__ */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* FSM_SYS_HDR_H */
