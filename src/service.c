/*******************************************************************************
 * File:        service.c
 * Project:     YourService
 * Description: Implements the systemd service logic for YourService.
 *
 * Author:      Peter Depuydt
 * Created on:  Dec 3rd, 2024
 * Version:     v1.0.0
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <syslog.h>
#include <unistd.h>
#include <systemd/sd-daemon.h>
#include "service.h"

// Global variables
static volatile int keep_running = 1;

// Signal handler for graceful shutdown
static void handle_signal(int signal) {
    if (signal == SIGINT || signal == SIGTERM) {
        syslog(LOG_INFO, "Received signal %d, shutting down...", signal);
        keep_running = 0;
    }
}

// Sets up signal handlers
static void setup_signal_handlers(void) {
    struct sigaction sa;
    sa.sa_handler = handle_signal;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, NULL) == -1 || sigaction(SIGTERM, &sa, NULL) == -1) {
        perror("Failed to set up signal handlers");
        exit(EXIT_FAILURE);
    }
}

// Initializes the service
bool service_init(void) {
    syslog(LOG_INFO, "Initializing the service...");
    setup_signal_handlers();

    // Add other initialization logic here (e.g., configuration, resource allocation)
    syslog(LOG_INFO, "Service initialization complete.");
    return true;
}

// Main service loop
void service_run(void) {
    syslog(LOG_INFO, "Entering the main service loop.");
    sd_notify(0, "STATUS=YourService is ready and running.");

    while (keep_running) {
        sd_notify(0, "WATCHDOG=1"); // Notify systemd that the service is alive
        sleep(30); // Simulate periodic task
        syslog(LOG_INFO, "Service is running...");
    }
    syslog(LOG_INFO, "Exiting the main service loop.");
}

// Cleans up resources before exiting
void service_cleanup(void) {
    syslog(LOG_INFO, "Performing cleanup...");
    // Add cleanup logic here (e.g., closing connections, freeing resources)
    syslog(LOG_INFO, "Cleanup complete.");
}

// EOF service.c