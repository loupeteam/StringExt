/*
 * This API provides information about the current AR boot mode.
 */

#ifndef _BOOT_MODE_API_H_
#define _BOOT_MODE_API_H_

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Returns true if the target is in RUN mode (if it finished booting successfully and user programs are running)
 * or if the target is currently booting towards RUN mode (which means that up until now no errors occured during boot).
 * Returns false, if the target is not in RUN mode and does not boot towards RUN mode (e.g. if it reboots or finished
 * rebooting after an error or after the user stopped the target via AS). */
bool bootModeIsRun();

#ifdef __cplusplus
}
#endif

#endif

