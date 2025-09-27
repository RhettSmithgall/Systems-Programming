#include "headers.h"

void printSymbols(struct symbol* head) {
    struct symbol* temp = head;
    while(temp != NULL) {
        printf("%d\t%s\t%X\n",
            temp->sourceline, temp->name, temp->address);
        temp = temp->next;
    }
}

