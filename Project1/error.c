#include "headers.h"

static error *errorHead;
static error *errorTail; 
static int count;

void init_errors() {
    errorHead = NULL;
    errorTail = NULL;
    count = 0;
}

int errorCount(){
    return count;
}

void addError(wordStruct* word,char* msg,int lineNum,int colNum){
    error *e = malloc(sizeof(error));

    e->lineNum = lineNum;
    e->colNum = colNum;
    strcpy(e->msg,msg);
    e->next = NULL;
    e->word = *word;

    if (errorTail) {
        errorTail->next = e;
    } else {
        errorHead = e;
    }
    errorTail = e;
    count++;

}

void printErrors(void) {
    if (count == 0) {
        printf("No errors found.\n");
        return;
    }

    printf("Encountered %d error(s):\n", count);

    error *curr = errorHead;  // assume this is your linked list head
    while (curr != NULL) {
        // Access wordStruct directly
        wordStruct w = curr->word;

        printf("%d:%d Error: %s\n", curr->lineNum, curr->colNum, curr->msg);
        printf(" %3d | %s\t%s\t%s\n", curr->lineNum, w.symbol, w.instruction, w.operand);
        printf("     | %*c\n", curr->colNum, '^');

        curr = curr->next;  // advance to next node
    }

}