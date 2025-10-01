#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

struct symbol {
	char name[7];
	int address;
	int sourceline; 
	struct symbol *next;
	};

typedef struct {
    char* symbol;
    int symcol;
    char* instruction;
    int inscol;
    char* operand;
    int opcol;
} wordStruct;

void getWord(char* readLine,wordStruct* word);
int isBlank(char* line);
void error(wordStruct word,char* message,int linenum,int col);
int isValidSymbolName(char* token);
void printSymbols(struct symbol* table);
void destroySymbolTable(struct symbol* head);
int symbolExists( struct symbol* table, char* token);
struct symbol* createSymbol(char* name, int address, int sourceline);
struct symbol* insertSymbol(struct symbol** head, char* name, int address, int sourceline);
int isOpcode(char* token);
int isDirective(char* token);
int isValidHex(char* input);
