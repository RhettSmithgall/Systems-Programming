#include "headers.h"

struct record* insertRecord(struct record** head, char* str) { //*head is a pointer to the pointer of the head
    struct record* newRecord = createRecord(str);
    if (*head == NULL) {
        *head = newRecord;
        return newRecord;
    }
    struct record* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newRecord;
    return newRecord;
}
