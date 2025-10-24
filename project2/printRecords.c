#include "headers.h"

void printRecords(struct record* head) {
    struct record* temp = head;

    while(temp != NULL) {
        printf("%s",temp->rec);
        temp = temp->next;
    }
}

