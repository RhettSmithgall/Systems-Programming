#include "headers.h"
void error(wordStruct word,char* message,int linenum,int col){
        printf("%d:%d Error: %s\n", linenum, col, message);
        printf(" %3d | %s\t%s\t%s\n",linenum,word.symbol,word.instruction,word.operand);
        printf("     | %*c\n",col,'^');
}