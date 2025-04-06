#include <stdio.h>
#include <string.h>
#include <time.h>
#include "execution.h" // Import the Execution Layer

// Logging function
void log_request(const char *action, const char *target, const char *status) {
    FILE *log_file = fopen("logs/security.log", "a");
    if (log_file == NULL) {
        printf("Error: Could not open log file.\n");
        return;
    }
    time_t now = time(NULL);
    fprintf(log_file, "%s - Action=%s, Target=%s, Status=%s\n", ctime(&now), action, target, status);
    fclose(log_file);
}

// Validate and execute function
void validate_and_execute(const char *action, const char *target, char *result) {
    const char *allowed_actions[] = {"read", "write", "create", "delete"};
    const char *restricted_files[] = {"/etc/passwd", "/etc/shadow"};
    int is_allowed = 0;

    // Check if the action is allowed
    for (int i = 0; i < 4; i++) {
        if (strcmp(action, allowed_actions[i]) == 0) {
            is_allowed = 1;
            break;
        }
    }

    if (!is_allowed) {
        strcpy(result, "Error: Action is not allowed.");
        log_request(action, target, "Blocked");
        return;
    }

    // Check if the target is restricted
    for (int i = 0; i < 2; i++) {
        if (strcmp(target, restricted_files[i]) == 0) {
            strcpy(result, "Error: Access to this file is restricted.");
            log_request(action, target, "Blocked");
            return;
        }
    }

    // Forward to Execution Layer
    execute_system_call(action, target, result);
    log_request(action, target, "Allowed");
}