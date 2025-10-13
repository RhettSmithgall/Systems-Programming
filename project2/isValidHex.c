#include "headers.h"

int isValidHex(char *input) {
    for (int i = 0; i < strlen(input); i++) {
        char c = input[i];
        if (!isxdigit(c)) {  
            return i + 1; //plus 1 because array index at 0 but we're sending the column number
        }
    }
    return 0;
}