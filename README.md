# FSM - Finite State Machine

## Description

Simple finite state machine (FSM) implementation in C for small embedded devices.

## Features

- FSM is written in C language
- FSM consumes a minimum amount of resources
- Support multiple instantiations of the state machine type
- Optionally the state machine can use separate entry/exit action functions for each state
- Optionally the state machine can pass runtime user data to each state on FSM initialization
- RTOS thread-safety support
  - Turn on RTOS thread-safety feature using `fsm_config.h` and `fsm_user_config.h` config files
  - Use in the project mutex OS abstraction interface in `fsm/system` folder
- Permissive Apache 2.0 license

## How to use library

1. Add library to the project

- Copy all `fsm` library folder to your project
- Add `fsm/src/include` folder to *include path* of your toolchain. This is where C/C++ compiler can find the files during compilation process. Usually using `-I` flag
- Add `fsm/src/fsm/fsm.c` source to toolchain build. These file is built by C/C++ compiler
- If your project is based on RTOS or OS, it is required to implement in the project mutex OS abstraction interface from `fsm/src/include/fsm/system/fsm_sys.h`. To enable RTOS thread-safety feature in library
  - Copy `fsm/src/include/fsm/fsm_user_config_template.h` to your project folder and rename it to `fsm_user_config.h`
  - Setup library RTOS related configurations (`FSM_CFG_OS` and `FSM_CFG_OS_MUTEX_HANDLE` macros) from `fsm/src/include/fsm/fsm_config.h` in created `fsm_user_config.h`
  - Copy from `fsm/src/fsm/system` one of implemented mutex OS abstraction interface `fsm_sys_xxxx.c` or create your own implementation

  If your project is not based on RTOS, then the library is require to disable RTOS related configurations in `fsm_user_config.h`.

2. Declare all FSM states

Declare FSM states in global scope and them functions

```c
#define FSM_STATE_1_ID 1
#define FSM_STATE_2_ID 2
#define FSM_STATE_3_ID 3

static fsm_state_t fsm_state_1 = {
    .id = FSM_STATE_1_ID,
    .ops = {
        .setup = state_1_setup,
        .enter = state_1_enter,
        .exit  = state_1_exit,
        .run   = state_1_run
    },
    .data = NULL /* Optional user data for this state */
};

static fsm_state_t fsm_state_2 = {
    .id = FSM_STATE_2_ID,
    .ops = {
        .setup = NULL,
        .enter = state_2_enter,
        .exit  = state_2_exit,
        .run   = state_2_run
    },
    .data = NULL
};

static fsm_state_t fsm_state_3 = {
    .id = FSM_STATE_3_ID,
    .ops = {
        .setup = state_3_setup,
        .enter = NULL,
        .exit  = NULL,
        .run   = state_3_run
    },
    .data = NULL
};
```

The state MUST bind related `run()` function. Another callbacks (`setup()`, `enter()`, `exit()`) are optional.

3. Create *states map* of your FSM

The states map is just a global array of `fsm_state_t*` structures pointers, which must be ended with `NULL`

```c
static fsm_state_t *fsm_states_map[] = {
    &fsm_state_1,
    &fsm_state_2,
    &fsm_state_3,
    NULL /* DO NOT FORGET THIS NULL AT THE END! */
};
```

4. Create FSM instance, initialize it and run in loop

```c
/**
 * \brief           Optional user data that passed to all states setup callback
 *                      on FSM initialization
 * \details         Usually used to pass to all states the specific data that
 *                      cannot be known at compile time, only when the firmware is executed
 *                      (on runtime)
 */
static user_data_t optional_setup_user_data;

/**
 * \brief           FSM instance
 */
static fsm_t fsm;

int main(void) {
    optional_setup_user_data = ...;

    fsm_init_params_t params = {
        .initial_state = &fsm_state_1,
        .states_map = fsm_states_map,
        .setup_data = &optional_setup_user_data
    };
    if (fsm_init(&fsm, &params) != fsmOK) {
        return 1;
    }

    while (1) {
        if (fsm_run(&fsm) != fsmOK) {
            return 2;
        }
    }

    return 0;
}
```

5. Use in the states callbacks `fsm_state_transition()` function to enter new state

```c
static fsmr_t state_1_run(fsm_state_t *state) {
    ...

    if (/* state transition condition */) {
        return fsm_state_transition(state->fsm, FSM_STATE_3_ID);
    }

    ...

    return fsmOK;
}
```
