#include "headers.h"

int isValidHex(char *input) {
    for (int i = 0; i < strlen(input); i++) {
        char c = input[i];
        if (!isxdigit(c)) {  // only 0–9 A–F a–f
            return 0;
        }
    }
    return 1;
}