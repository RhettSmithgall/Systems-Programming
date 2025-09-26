#include "headers.h"

char* opcodes[] = {
    "ADD","ADDF","ADDR","AND","CLEAR","COMP","COMPF","COMPR",
    "DIV","DIVF","DIVR","FIX","FLOAT","HIO","J","JEQ","JGT","JLT",
    "JSUB","LDA","LDB","LDCH","LDF","LDL","LDS","LDT","LDX","LPS",
    "MUL","MULF","MULR","NORM","OR","RD","RMO","RSUB","SHIFTL",
    "SHIFTR","SIO","SSK","STA","STB","STCH","STF","STI","STL","STS",
    "STSW","STT","STX","SUB","SUBF","SUBR","SVC","TD","TIO","TIX",
    "TIXR","WD"};

int isOpcode(char* token) {
    
    //https://www.geeksforgeeks.org/c/length-of-array-in-c/
    //this works because of pointer trickery
    int n = sizeof(opcodes) / sizeof(opcodes[0]); //basically n = length(opcodes)
    
    for(int i = 0; i < n; i++) {
        if ( strcmp(token, opcodes[i]) == 0 ) {
            return 1; 
        }
    }
    return 0; 
}