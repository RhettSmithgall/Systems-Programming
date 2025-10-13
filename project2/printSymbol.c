#include "headers.h"

void printSymbols(struct symbol* head) {
    struct symbol* temp = head;
    while(temp != NULL) {
        printf("%s\t%X\n",
            temp->name, temp->address);
        temp = temp->next;
    }
}

