#include "headers.h"

int getSymbolAddress(struct symbol* head,char* token) {
    struct symbol* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, token) == 0) {
            return temp->address; 
        }
        temp = temp->next;
    }
    return 0; 
}