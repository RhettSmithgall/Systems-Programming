//a struct for a symbol table
//its a linked list with more than one data in it's node
struct symbol {
	char name[7];
	int address;
	int sourceline; 
	struct symbol *next;
	};

//function defintions
int getSymbolAddress(struct symbol* head,char* token);
void printSymbols(struct symbol* table);
void destroySymbolTable(struct symbol* head);
int symbolExists( struct symbol* table, int address);
struct symbol* createSymbol(char* name, int address, int sourceline);
struct symbol* insertSymbol(struct symbol** head, char* name, int address, int sourceline);