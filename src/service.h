/*******************************************************************************
 * File:        service.h
 * Project:     YourService
 * Description: Implements the systemd service logic for YourService.
 *
 * Author:      Peter Depuydt
 * Created on:  Dec 3rd, 2024
 * Version:     v1.0.0
 ******************************************************************************/

#ifndef SERVICE_H
#define SERVICE_H

#include <stdbool.h>

// Initializes the service. Returns true on success, false on failure.
bool service_init(void);

// Main service loop. Runs until interrupted.
void service_run(void);

// Cleans up resources before exiting.
void service_cleanup(void);

#endif /* SERVICE_H */

// EOF service.h
