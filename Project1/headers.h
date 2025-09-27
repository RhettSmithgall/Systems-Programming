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

int isValidSymbolName(char* token);
void printSymbols(struct symbol* table);
void destroySymbolTable(struct symbol* head);
int symbolExists( struct symbol* table, char* token);
struct symbol* createSymbol(char* name, int address, int sourceline);
struct symbol* insertSymbol(struct symbol** head, char* name, int address, int sourceline);
int isOpcode(char* token);
int isDirective(char* token);
int isValidHex(char* input);
