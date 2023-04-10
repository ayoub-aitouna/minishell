#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** find_duplicates(char** input) {
    int len = 0, i, j, k;
    char** result = NULL;

    // Count number of strings in the array
    while (input[len] != NULL) {
        len++;
    }

    // Allocate memory for result array
    result = (char**) malloc(sizeof(char*) * len);
    if (result == NULL) {
        printf("Error: Failed to allocate memory.\n");
        return NULL;
    }

    // Check for duplicates
    int count = 0;
    for (i = 0; i < len; i++) {
        for (j = i+1; j < len; j++) {
            if (strcmp(input[i], input[j]) == 0) {
                // Found a duplicate
                // Get the value of the last duplicate
                for (k = j; k < len; k++) {
                    if (strcmp(input[k], input[j]) == 0) {
                        result[count] = strchr(input[k], '=') + 1;
                    }
                }
                count++;
            }
        }
    }

    // If no duplicates were found, return NULL
    if (count == 0) {
        free(result);
        return NULL;
    }

    // Resize the result array to the number of duplicates found
    result = (char**) realloc(result, sizeof(char*) * count);
    if (result == NULL) {
        printf("Error: Failed to allocate memory.\n");
        return NULL;
    }

    return result;
}

int main() {
    char* strings[] = {"foo=1", "foo=2", "foo=3", "qux=4", "foo=5", NULL};
    char** duplicates = find_duplicates(strings);
    if (duplicates != NULL) {
        printf("Duplicates found:\n");
        for (int i = 0; duplicates[i] != NULL; i++) {
            printf("%s\n", duplicates[i]);
        }
        free(duplicates);
    } else {
        printf("No duplicates found.\n");
    }
    return 0;
}


