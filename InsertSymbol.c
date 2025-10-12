#include "headers.h"

struct symbol* insertSymbol(struct symbol** head, char* name, int address, int sourceline) { //*head is a pointer to the pointer of the head
    struct symbol* newSymbol = createSymbol(name, address, sourceline);
    if (*head == NULL) {
        *head = newSymbol;
        return newSymbol;
    }
    struct symbol* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newSymbol;
    return newSymbol;
}
