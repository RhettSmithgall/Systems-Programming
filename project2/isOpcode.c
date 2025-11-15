#include "headers.h"

char* ops[] = {
    "ADD","ADDF","ADDR","AND","CLEAR","COMP","COMPF","COMPR",
    "DIV","DIVF","DIVR","FIX","FLOAT","HIO","J","JEQ","JGT","JLT",
    "JSUB","LDA","LDB","LDCH","LDF","LDL","LDS","LDT","LDX","LPS",
    "MUL","MULF","MULR","NORM","OR","RD","RMO","RSUB","SHIFTL",
    "SHIFTR","SIO","SSK","STA","STB","STCH","STF","STI","STL","STS",
    "STSW","STT","STX","SUB","SUBF","SUBR","SVC","TD","TIO","TIX",
    "TIXR","WD"};
/*
@brief checks a string to see if its a sic assembly instruction
@param token the string to check
@return 1 yes it is an instruction or 0 no it isn't
*/
int isOpcode(char* token) {
    
    //https://www.geeksforgeeks.org/c/length-of-array-in-c/
    //this works because of pointer trickery
    int n = sizeof(ops) / sizeof(ops[0]); //basically n = length(opcodes)
    
    for(int i = 0; i < n; i++) {
        if ( strcmp(token, ops[i]) == 0 ) {
            return 1; 
        }
    }
    return 0; 
}