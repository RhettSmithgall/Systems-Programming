#include "headers.h"

void destroyRecords(struct record* head) {
    if (head == NULL) {
        return;  
    }
    struct record* next = head->next;  
    free(head);
    destroyRecords(next);  
}
