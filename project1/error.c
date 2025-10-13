#include "headers.h"


void error(char* filename, wordStruct* word,char* message,int linenum,int col){
        printf("%s:%d:%d %sERROR: %s%s\n", filename, linenum, col,KRED,KNRM,message);
        
int sym_len = strlen(word->symbol);
int instr_len = strlen(word->instruction);

if (col < sym_len) {
    // Make symbol green
    printf(" %3d |  %s%s%s\t%s\t%s\n", linenum,KGRN,word->symbol,KNRM,word->instruction, word->operand);
} else if (col < sym_len + 1 + instr_len) {  // +1 for the tab/space between fields
    // Make instruction green
    printf(" %3d |  %s\t%s%s%s\t%s\n", linenum,word->symbol,KGRN,word->instruction,KNRM,word->operand);
} else {
    // Make operand green
    printf(" %3d |  %s\t%s\t%s%s%s\n", linenum, word->symbol, word->instruction,KGRN,word->operand,KNRM);
}

	if(col > 0){ col -= 1;} //i do not even pretend to know why it gets offset like this

	//printf(" %3d | %s\t%s\t%s\n",linenum,word->symbol,word->instruction,word->operand);
        printf("     |  %s%*c%s\n",KGRN,col,'^',KNRM);
}
