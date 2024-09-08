/**
 * \file            fsm_sys_freertos.c
 * \brief           System functions for FreeRTOS based operating system
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

#include "FreeRTOS.h"
#include "semphr.h"

uint8_t fsm_sys_mutex_create(FSM_CFG_OS_MUTEX_HANDLE *mutex) {
    *mutex = xSemaphoreCreateMutex();
    return *mutex != NULL;
}

uint8_t fsm_sys_mutex_wait(FSM_CFG_OS_MUTEX_HANDLE *mutex) {
    return xSemaphoreTake(*mutex, portMAX_DELAY) == pdPASS;
}

uint8_t fsm_sys_mutex_release(FSM_CFG_OS_MUTEX_HANDLE *mutex) {
    return xSemaphoreGive(*mutex) == pdPASS;
}

#endif /* FSM_CFG_OS && !__DOXYGEN__ */
