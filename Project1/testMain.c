#include "headers.h"
#include <ctype.h>
#include <string.h>

int isWhiteSpace(char str[]);

/*
what is needed for this program?
a symbol table that tracks:
the name (7 characters)
the address 
>cool feature< the sourceline

this can be implemented in a linked link, remember that singly linked lists require a pointer to the next
list item


make the compiler make a 64bit executable!!!!!
*/

//GET PRINT SYMBOL TABLE WORKING!!!

//

int main(int argc,char* argsv[]){
	FILE *file;
	char line[1024];
	
	for(int i=0;i<argc;i++){
		//printf("#%i %s \n",i,argsv[i]);
	}

	if(argc != 2){
		printf("please don't!");
	}
	
	file = fopen(argsv[1],"r");

	char liney[100];
	int counter = 1;
    int address = 4096;

	struct symbol myTable = NULL;
	
	if(file != NULL){
		while(fgets(line,1023,file) != NULL){
			
			if(isWhiteSpace(line)){
				printf("EMPTY LINE!!!!");
				break;
			}

			char test = line[0];
			if(test == '#'){
				//printf("this is a comment \n");
			}
			else{
				if(!isspace(line[0])){

				sscanf(line,"%s",liney);

				//printf("#%d: %s %X\n",counter,liney,address);
				insertSymbol(myTable, liney, address, counter);
				}
			}
			counter++;
            address += 3;
		}
	}
	else{
		printf("no file :(");
	}

	PrintSymbols(myTable);
	
	fclose(file);
	
	return 0;
}

int isWhiteSpace(char str[]){
	int spaceCount = 0;

	for(int i=0;i<strlen(str);i++){
		if(isspace(str[i])){
			spaceCount++;
		}
	}
	if(spaceCount == strlen(str)){
		return 1;
	}
	else {return 0;}
}

/*
void InsertSymbol( SYMTAB table, char n[7], int addr, int source){

	struct symbol newsym;

	newsym.name = n;
	newsym.address = addr;
	newsym.sourceline = source
}
*/
