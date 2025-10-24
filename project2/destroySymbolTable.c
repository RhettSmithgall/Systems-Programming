#include "headers.h"

void destroySymbolTable(struct symbol* head) {
    if (head == NULL) {
        return; 
    }
    struct symbol* next = head->next;  
    free(head);
    destroySymbolTable(next);  
}
