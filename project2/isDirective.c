#include "headers.h"

char* directives[] = {"START","END","BYTE","WORD","RESB","RESW","RESR","EXPORTS"};

/*
@brief checks a string to see if its a sic assembly directive 
@param token a string to check
@return yes 1 its a directive or no 0 it isn't
*/
int isDirective(char* token) {
    //https://www.geeksforgeeks.org/c/length-of-array-in-c/
    //this works because of pointer trickery
    int n = sizeof(directives) / sizeof(directives[0]); //basically n = length(directives)

    for(int i = 0; i < n; i++) {
        if ( strcmp(token, directives[i]) == 0 ) {
            return 1; 
        }
    }
    return 0; 
}

