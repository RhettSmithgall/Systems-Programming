#include "headers.h"

int isBlank(char *line) {
    for (int i = 0; line[i] != '\n'; i++) {
        if (!isspace(line[i])) {
            return 0; 
        }
    }
    return 1; 
}
