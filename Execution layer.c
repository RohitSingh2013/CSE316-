#include <stdio.h>
#include <stdlib.h>

// Execute system call function
void execute_system_call(const char *action, const char *target, char *result) {
    if (strcmp(action, "read") == 0) {
        FILE *file = fopen(target, "r");
        if (file == NULL) {
            sprintf(result, "Error: Could not open file '%s'.", target);
            return;
        }
        char content[500];
        fread(content, 1, sizeof(content) - 1, file);
        content[sizeof(content) - 1] = '\0';
        fclose(file);
        sprintf(result, "File Content:\n%s", content);
    } else if (strcmp(action, "write") == 0) {
        FILE *file = fopen(target, "w");
        if (file == NULL) {
            sprintf(result, "Error: Could not write to file '%s'.", target);
            return;
        }
        fprintf(file, "Sample content");
        fclose(file);
        sprintf(result, "Written to file: %s", target);
    } else if (strcmp(action, "create") == 0) {
        if (mkdir(target) == 0) {
            sprintf(result, "Created directory: %s", target);
        } else {
            sprintf(result, "Error: Could not create directory '%s'.", target);
        }
    } else if (strcmp(action, "delete") == 0) {
        if (remove(target) == 0) {
            sprintf(result, "Deleted file: %s", target);
        } else {
            sprintf(result, "Error: Could not delete file '%s'.", target);
        }
    } else {
        strcpy(result, "Error: Unknown action.");
    }
}