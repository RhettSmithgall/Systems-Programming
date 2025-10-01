#include "headers.h"

wordStruct* getWord(char* readLine){
    char* tokens[3] = {NULL, NULL, NULL};
    int tokcol[3];
    int toknum = 0;
    int colnum = 0;
    int j = 0;
    char buffer[1024];
    wordStruct *word = malloc(sizeof(wordStruct));
    
    //this very very ugly block of code reads in the line 1 character at a time to perserve column numbers
    while(readLine[colnum] != '\n' && toknum < 3){ //read the line character by character 
        if(!isspace(readLine[colnum])){ //if the character isn't whitespace, start loading it into a buffer 
            buffer[j] = readLine[colnum]; 
            j++; 
        } 
        else if(j > 0){ //when you reach the end of a character, load the buffer into a more permanent place 
            buffer[j] = '\0'; 
            tokens[toknum] = malloc(strlen(buffer)+1); 
            strcpy(tokens[toknum], buffer); 
            tokcol[toknum] = colnum - strlen(buffer); 
            toknum++; 
            j = 0; 
        } 
        colnum++; 
    } 
    if(j > 0 && toknum < 3){ //make sure something leftover in the buffer doesn't get forgotten 
        buffer[j] = '\0'; 
        tokens[toknum] = malloc(strlen(buffer)+1); 
        strcpy(tokens[toknum], buffer); 
        tokcol[toknum] = colnum - strlen(buffer); 
        toknum++; 
        j = 0; 
    }

    //this block takes the 3 tokens from previous and sorts them into what they are
    //1 token is a single instruction like resb
    //2 tokens is an instruction + operand pair
    //and 3 tokens is the full SYMBOL INSTRUCTION OPERAND word
    if(toknum == 1){
        word->symbol[0] = '\0';
        strcpy(word->instruction, tokens[0]);
        word->inscol = tokcol[0] + 4;
        word->operand[0] = '\0';
    }
    else if(toknum == 2){
        word->symbol[0] = '\0';
        strcpy(word->instruction, tokens[0]);
        word->inscol = tokcol[0] + 4;
        strcpy(word->operand, tokens[1]);
        word->opcol = tokcol[1] + 8;
    } else if(toknum > 2){
        strcpy(word->symbol, tokens[0]);
        word->symcol = tokcol[0];
        strcpy(word->instruction, tokens[1]);
        word->inscol = tokcol[1] + 4;
        strcpy(word->operand, tokens[2]);
        word->opcol = tokcol[2] + 8;
    }

    for (int i = 0; i < toknum; i++) {
        free(tokens[i]);
    }

    //printf("word in function: %s\t%s\t%s\n",word->symbol,word->instruction,word->operand);
    return word;
}