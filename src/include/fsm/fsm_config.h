/**
 * \file            fsm_config.h
 * \brief           FSM default configurations file
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

#ifndef FSM_HDR_DEFAULT_CONFIG_H
#define FSM_HDR_DEFAULT_CONFIG_H

/* Uncomment to ignore user options (or set macro in compiler flags) */
/* #define FSM_IGNORE_USER_OPTS */

/* Include application options */
#ifndef FSM_IGNORE_USER_CONFIGS
#include "fsm_user_config.h"
#endif /* FSM_IGNORE_USER_CONFIGS */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \defgroup        FSM_CFG Configuration
 * \brief           FSM configurations
 * \{
 */

/**
 * \brief           Enables `1` or disables `0` operating system support in the library
 *
 * \note            When `FSM_CFG_OS` is enabled, user must implement functions in \ref FSM_SYS group.
 */
#ifndef FSM_CFG_OS
#define FSM_CFG_OS                 0
#endif

/**
 * \brief           Mutex handle type
 *
 * \note            This value must be set in case \ref FSM_CFG_OS is set to `1`.
 *                  If data type is not known to compiler, include header file with
 *                  definition before you define handle type
 */
#ifndef FSM_CFG_OS_MUTEX_HANDLE
#define FSM_CFG_OS_MUTEX_HANDLE    void *
#endif

/**
 * \}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* FSM_HDR_DEFAULT_CONFIG_H */
