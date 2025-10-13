#include "headers.h"

// Forbidden characters
const char forbidden[] = ",$!=+-()@";

int isValidSymbolName(char* token) {
    // Check if first character is A-Z
    if (!isalpha(token[0])) {
        return 0;
    }

    // Check length <= 6
    if (strlen(token) > 6) {
        return 0;
    }

    // Check for forbidden characters
    for (int i = 0; token[i] != '\0'; i++) {
        if (strchr(forbidden, token[i]) != NULL) {
            return 0;
        }
    }

    return 1;
}