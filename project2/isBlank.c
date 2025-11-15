#include "headers.h"

/*
@brief tells whether or not the given line is blank (all spaces, tabs and newlines)
@param line the string line to check
@return true 0 or false 1
*/
int isBlank(char *line) {
    for (int i = 0; line[i] != '\n'; i++) {
        if (!isspace(line[i])) {
            return 0; 
        }
    }
    return 1; 
}
