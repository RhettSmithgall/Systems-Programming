//check if a symbol exists
#include "headers.h"

int symbolExists(struct symbol* head,char* token) {
    struct symbol* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, token) == 0) {
            return 1; 
        }
        temp = temp->next;
    }
    return 0; 
}