#include "headers.h"

struct symbol* createSymbol(char* name, int address, int sourceline) { 
    struct symbol* newNode = (struct symbol*)malloc(sizeof(struct symbol)); 

    strcpy(newNode->name, name);
    newNode->address = address;
    newNode->sourceline = sourceline;
    newNode->next = NULL;
    return newNode;
}
