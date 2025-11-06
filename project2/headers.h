//header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "record.h"
#include "symbol.h"

// colors.h
#ifndef COLORS_H
#define COLORS_H

#if defined(_WIN32) || defined(_WIN64)
    // Windows escape sequence (GCC on MSYS2/MinGW supports ANSI)
    //text colors
    #define KNRM  "\033[0m"
    #define KRED  "\033[31m"
    #define KGRN  "\033[32m"
    #define KYEL  "\033[33m"
    #define KBLU  "\033[34m"
    #define KMAG  "\033[35m"
    #define KCYN  "\033[36m"
    #define KWHT  "\033[37m"
#else
    // Mainframe / z/OS escape sequence
    #define KNRM  "\x27[0m"
    #define KRED  "\x27[31m"
    #define KGRN  "\x27[32m"
    #define KYEL  "\x27[33m"
    #define KBLU  "\x27[34m"
    #define KMAG  "\x27[35m"
    #define KCYN  "\x27[36m"
    #define KWHT  "\x27[37m"
#endif

#endif // COLORS_H

//a struct for a SIC Assembly WORD
typedef struct {
    char symbol[128];
    int symcol;
    char instruction[128];
    int inscol;
    char operand[128];
    int opcol;
} wordStruct;

//function defintions
int IBM2ISO(int number);
wordStruct* getWord(char* readLine);
int toOpcode(char* token);
int isBlank(char* line);
void error(char* filename,char* line,wordStruct* word,char* message,int linenum,int col);
int isOpcode(char* token);
int isDirective(char* token);
int isValidHex(char* input);
void autograph();
