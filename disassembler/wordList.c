#include "headers.h"
//all about words

//creates a word 
wordStruct* createWord(char* symbol,char* instruction,char* operand) { 
    wordStruct* newWord = (wordStruct*)malloc(sizeof(wordStruct)); 

    strcpy(newWord->symbol,symbol);
    strcpy(newWord->symbol,instruction);
    strcpy(newWord->symbol,operand);
    newWord->next = NULL;
    return newWord;
}

//inserts a word to the end of the list
wordStruct* insertword(wordStruct** head, wordStruct* newWord) { //*head is a pointer to the pointer of the head
    if (*head == NULL) {
        *head = newWord;
        return newWord;
    }

    wordStruct* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newWord;
    return newWord;
}

//destroys the entire word list
void destroywords(wordStruct* head) {
    if (head == NULL) {
        return;  
    }
    wordStruct* next = head->next;  
    free(head);
    destroywords(next);  
}

//print the words to a file 
void fprintwords(FILE *fp,wordStruct* head) {
    wordStruct* temp = head;

    while(temp != NULL) {
        fprintf(fp,"%s\t%s\t%s",temp->symbol,temp->instruction,temp->operand);
        temp = temp->next;
    }
}

//print the word table to stdout
void printwords(wordStruct* head) {
    wordStruct* temp = head;

    while(temp != NULL) {
        printf("%s\t%s\t%s",temp->symbol,temp->instruction,temp->operand);
        temp = temp->next;
    }
}