#include "headers.h"
void error(char* filename, wordStruct* word,char* message,int linenum,int col){
        printf("%s:%d:%d\x27[31m ERROR: \x27[0m %s\n", filename, linenum, col, message);
        
int sym_len = strlen(word->symbol);
int instr_len = strlen(word->instruction);

if (col < sym_len) {
    // Make symbol green
    printf(" %3d |  \x27[32m%s\x27[0m\t%s\t%s\n", linenum, word->symbol, word->instruction, word->operand);
} else if (col < sym_len + 1 + instr_len) {  // +1 for the tab/space between fields
    // Make instruction green
    printf(" %3d |  %s\t\x27[32m%s\x27[0m\t%s\n", linenum, word->symbol, word->instruction, word->operand);
} else {
    // Make operand green
    printf(" %3d |  %s\t%s\t\x27[32m%s\x27[0m\n", linenum, word->symbol, word->instruction, word->operand);
}

	if(col > 0){ col -= 1;} //i do not even pretend to know why it gets offset like this

	//printf(" %3d | %s\t%s\t%s\n",linenum,word->symbol,word->instruction,word->operand);
        printf("     |  \x27[32m%*c\x27[0m\n",col,'^');
}
