#include "headers.h"

/*
Symbols
1. Symbols cannot be defined with a name which matches an assembler directive -> taken care of somewhere else
2. Symbols must start with an alpha character [A-Z]
3. Symbols cannot be longer than six characters
4. Symbols cannot contain spaces, $, !, =, +, - , (, ), or@
*/

int isValidSymbolName(char* token) {
    while(*token != '\0'){
        if(!isalpha(*token)){
            return 0;
        }
        token++;
    }
    return 1; 
}