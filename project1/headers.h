//header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

//a struct for a symbol table
struct symbol {
	char name[7];
	int address;
	int sourceline; 
	struct symbol *next;
	};

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
wordStruct* getWord(char* readLine);
int isBlank(char* line);
void error(char* filename, wordStruct* word,char* message,int linenum,int col);
int isValidSymbolName(char* token);
void printSymbols(struct symbol* table);
void destroySymbolTable(struct symbol* head);
int symbolExists( struct symbol* table, char* token);
struct symbol* createSymbol(char* name, int address, int sourceline);
struct symbol* insertSymbol(struct symbol** head, char* name, int address, int sourceline);
int isOpcode(char* token);
int isDirective(char* token);
int isValidHex(char* input);
void autograph();
