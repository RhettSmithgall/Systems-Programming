#include "headers.h"

void destroySymbolTable(struct symbol* head) {
    if (head == NULL) {
        return;  // Base case: end of list
    }
    struct symbol* next = head->next;  // Save next pointer before freeing
    free(head);
    destroySymbolTable(next);  // Recurse on the saved next pointer
}
