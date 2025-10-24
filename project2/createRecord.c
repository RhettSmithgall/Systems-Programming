#include "headers.h"

struct record* createRecord(char* str) { 
    struct record* newRecord = (struct record*)malloc(sizeof(struct record)); 

    strcpy(newRecord->rec, str);
    newRecord->next = NULL;
    return newRecord;
}
