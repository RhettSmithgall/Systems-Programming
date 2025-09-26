#include "headers.h"

int main( int argc, char*   argv[]   ){
	FILE *fp;
	int i;
	char line[1024];

	char *token;
	char *search = " \t\n\r"; 

	SYMTAB MySymbolTable;
    MySymbolTable = NULL;

	MySymbolTable =	InsertSymbol(MySymbolTable, "Scott" , 1000, 22);
	PrintSymbols(MySymbolTable);
	
	MySymbolTable =	InsertSymbol(MySymbolTable, "Brennan", 2000, 55);
	PrintSymbols(MySymbolTable);

	if ( argc !=2 ) {
	printf("ERROR: USAGE is %s <filename>\n", argv[0] );
	return 0; 
	}


	fp = fopen( argv[1], "r"  );

	if ( fp == NULL ) {
		printf("Error: %s could not be opened for reading\n", argv[1]);
		return -1;
	}


	while( fgets(line, 1023, fp) != NULL   ){


	printf("%s\n", line);


	if ( line[0] == '#'   ) {
		printf("COMMENT LINE: %s\n", line);
		continue;	
	}

	if ( line[0] == '\n'      ) {
		printf("ERROR. Blank LInes are not allowed\n");
		fclose(fp);
		return -1;
	}

	/* if we got here...we need to tokenize the line and "figure out" 
		what's on the line so we can calculate how much space in memory
		this line of the assembler program will occupy  */ 
	printf("Here are the tokens for the line:\n");
	token = strtok(line, search);
	while( token != NULL ){
		printf("Token is %s\n", token);
		token = strtok(NULL, search);
	}
	





	}


	fclose(fp);
	return 0;
}
