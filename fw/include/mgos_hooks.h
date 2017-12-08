/*
 * Copyright (c) 2014-2017 Cesanta Software Limited
 * All rights reserved
 */

/*
 * Hooks API.
 *
 * Mongoose OS provides a way to get a notification when certain event
 * happens. Possible event types are specified by the `enum mgos_hook_type`.
 * User code can register a handler which gets called when an event
 * happens. Event parameters are passed as a pointer to a structure that
 * depends on an event type.
 */

#ifndef CS_FW_SRC_MGOS_HOOKS_H_
#define CS_FW_SRC_MGOS_HOOKS_H_

#include <stdbool.h>

#include "mgos_debug.h"
#include "mgos_sys_config.h"
#include "mgos_updater_common.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum mgos_hook_type {
  /*
   * Fired when all core modules and libs are initialized (Right after printing
   * `Init done` to the console).
   */
  MGOS_HOOK_INIT_DONE,

  /*
   * Fired when anything is printed to the debug console, see `struct
   * mgos_debug_hook_arg`
   */
  MGOS_HOOK_DEBUG_WRITE,

  /*
   * Fired right before restarting the system (but also before unmounting
   * filesystems, disconnecting from the wifi, etc)
   */
  MGOS_HOOK_SYSTEM_RESTART,

  /*
   * Fired when OTA status is changed; see `struct mgos_ota_status`
   */
  MGOS_HOOK_OTA_STATUS,

  MGOS_HOOK_TYPES_CNT
};

struct mgos_hook_arg {
  union {
    /* Arguments for the `MGOS_HOOK_DEBUG_WRITE` event */
    struct mgos_debug_hook_arg debug;
    /* Arguments for the `MGOS_HOOK_OTA_STATUS` event */
    struct mgos_ota_status ota_status;
  };
};

/*
 * Hook function, `arg` is a hook-specific arguments, `userdata` is an
 * arbitrary pointer given at the hook registration time.
 */
typedef void(mgos_hook_fn_t)(enum mgos_hook_type type,
                             const struct mgos_hook_arg *arg, void *userdata);

/* Register event handler. */
bool mgos_hook_register(enum mgos_hook_type type, mgos_hook_fn_t *cb,
                        void *userdata);

/* Trigger an event. */
void mgos_hook_trigger(enum mgos_hook_type type,
                       const struct mgos_hook_arg *arg);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CS_FW_SRC_MGOS_HOOKS_H_ */