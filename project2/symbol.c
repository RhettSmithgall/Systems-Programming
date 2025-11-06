#include "headers.h"

//create symbol
struct symbol* createSymbol(char* name, int address, int sourceline) { 
    struct symbol* newNode = (struct symbol*)malloc(sizeof(struct symbol)); 

    strcpy(newNode->name, name);
    newNode->address = address;
    newNode->sourceline = sourceline;
    newNode->next = NULL;
    return newNode;
}

int symbolExists(struct symbol* head,char* token) {
    struct symbol* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, token) == 0) {
            return temp->sourceline; 
        }
        temp = temp->next;
    }
    return 0; 
}

//insert a symbol at the end of the list
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

//frees the whole symbol list
void destroySymbolTable(struct symbol* head) {
    if (head == NULL) {
        return; 
    }
    struct symbol* next = head->next;  
    free(head);
    destroySymbolTable(next);  
}

void printSymbols(struct symbol* head) {
    struct symbol* temp = head;
    while(temp != NULL) {
        printf("%s\t%X\n",
            temp->name, temp->address);
        temp = temp->next;
    }
}

//finds the symbol in the list and returns the address
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