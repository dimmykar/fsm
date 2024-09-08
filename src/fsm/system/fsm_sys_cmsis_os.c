/**
 * \file            fsm_sys_cmsis_os.c
 * \brief           System functions for CMSIS-OS based operating system
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

#include "fsm/system/fsm_sys.h"

#if FSM_CFG_OS && !__DOXYGEN__

#include "cmsis_os.h"

uint8_t fsm_sys_mutex_create(FSM_CFG_OS_MUTEX_HANDLE* mutex) {
    const osMutexAttr_t attr = {
        .name = "fsm_mutex",
        .attr_bits = osMutex,
    };
    return (*mutex = osMutexNew(&attr)) != NULL;
}

uint8_t fsm_sys_mutex_wait(FSM_CFG_OS_MUTEX_HANDLE* mutex) {
    return osMutexAcquire(*mutex, osWaitForever) == osOK;
}

uint8_t fsm_sys_mutex_release(FSM_CFG_OS_MUTEX_HANDLE* mutex) {
    return osMutexRelease(*mutex) == osOK;
}

#endif /* FSM_CFG_OS && !__DOXYGEN__ */
