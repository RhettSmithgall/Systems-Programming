#include "headers.h"

void destroySymbolTable(struct symbol* head) {
    struct symbol* temp = head;
    free(head);
    destroySymbolTable(temp->next);
}