#include "headers.h"
//all about records

//creates a record 
struct record* createRecord(char* str) { 
    struct record* newRecord = (struct record*)malloc(sizeof(struct record)); 

    strcpy(newRecord->rec, str);
    newRecord->next = NULL;
    return newRecord;
}

//inserts a record to the end of the list
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

//destroys the entire record list
void destroyRecords(struct record* head) {
    if (head == NULL) {
        return;  
    }
    struct record* next = head->next;  
    free(head);
    destroyRecords(next);  
}

//print the records to a file 
void fprintRecords(FILE *fp,struct record* head) {
    struct record* temp = head;

    while(temp != NULL) {
        fprintf(fp,"%s",temp->rec);
        temp = temp->next;
    }
}

//print the record table to stdout
void printRecords(struct record* head) {
    struct record* temp = head;

    while(temp != NULL) {
        printf("%s",temp->rec);
        temp = temp->next;
    }
}