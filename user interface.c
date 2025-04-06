#include <stdio.h>
#include <string.h>
#include "security.h" // Import the Security Layer

void main() {
    printf("Welcome to the Secure System Call Interface!\n");
    char command[256];
    while (1) {
        printf("Enter a command (e.g., 'read file.txt', 'exit'): ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0'; // Remove trailing newline

        if (strcmp(command, "exit") == 0) {
            printf("Exiting...\n");
            break;
        }

        char action[50], target[200];
        int parsed = sscanf(command, "%s %s", action, target);

        if (parsed < 2) {
            printf("Invalid command format. Example: 'read file.txt'\n");
            continue;
        }

        // Send the command to the Security Layer
        char result[500];
        validate_and_execute(action, target, result);
        printf("%s\n", result);
    }
}