#include "headers.h"
void error(char* filename,char* line,wordStruct* word,char* message,int linenum,int col){
    printf("%s:%d:%d %sERROR:%s %s\n", filename, linenum, col,KRED,KNRM,message);
        
    int n = strlen(line);

    int startColor;
    int endColor;

    if(col < word->inscol){ //error is in the symbol
        startColor = 0;
        endColor = word->inscol-1;
    }
    else if(col < word->opcol){ //error is in the instruction
        startColor = word->inscol;
        endColor = word->opcol-1;
    }else{ //error is in the operand
        startColor = word->opcol ;
        endColor = n - 1;
    }

    printf(" %3d | ",linenum);
    for(int i = 0;i<n;i++){
        if(i == startColor){
            printf("%s",KGRN);
        }

        printf("%c",line[i]);

        if(i == endColor){
            printf("%s",KNRM);
        }
    }

    printf("     | ");
    for(int i = 0;i<n;i++){
        if(startColor == i){
            printf("%s",KGRN);
        }

        if(isspace(line[i])){
            printf("%c",line[i]);
        }
        else{

            if(i == col){
                printf("^");
            }
            else if(startColor <= i && i <= endColor){
                printf("~");
            }
            else{
                printf(" ");
            }
        }

        if(endColor == i){
            printf("%s",KNRM);
        }
    }
}
