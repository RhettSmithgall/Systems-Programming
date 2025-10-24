#include "headers.h"

void fprintRecords(FILE *fp,struct record* head) {
    struct record* temp = head;

    while(temp != NULL) {
        fprintf(fp,"%s",temp->rec);
        temp = temp->next;
    }
}

