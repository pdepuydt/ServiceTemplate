/*******************************************************************************
 * File:        main.c
 * Project:     YourService
 * Description: Entry point for the YourService service.
 *
 * Author:      Peter Depuydt
 * Created on:  Dec 3rd, 2024
 * Version:     v1.0.0
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <systemd/sd-daemon.h>
#include "service.h"

int main() {
    // Initialize syslog
    openlog("YourService", LOG_PID | LOG_CONS, LOG_USER);

    // Notify systemd that the service is starting
    sd_notify(0, "STATUS=Starting YourService; please wait...");

    // Initialize the service
    if (!service_init()) {
        syslog(LOG_ERR, "Failed to initialize the service.");
        sd_notify(0, "STATUS=Failed to initialize; exiting.");
        return EXIT_FAILURE;
    }

    // Notify systemd that the service is ready
    sd_notify(0, "READY=1");

    // Start the main service loop
    service_run();

    // Cleanup before exit
    service_cleanup();

    // Notify systemd that the service is stopping
    sd_notify(0, "STOPPING=1");
    syslog(LOG_INFO, "Service has stopped.");

    return EXIT_SUCCESS;
}

/* EOF main.c */
