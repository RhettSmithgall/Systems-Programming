#include "headers.h"

int isValidHex(char *input) {
    for (int i = 0; i < strlen(input); i++) {
        char c = input[i];
        if (!isxdigit(c)) {  
            return 0;
        }
    }
    return 1;
}