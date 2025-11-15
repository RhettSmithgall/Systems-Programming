//a struct for a record table
//it's a linked list for strings
struct record {
	char rec[128];
	struct record *next;
	};

//function defintions
void fprintRecords(FILE *fp,struct record* head);
void printRecords(struct record* head);
struct record* createRecord(char* str);
struct record* insertRecord(struct record** head, char* str);
void destroyRecords(struct record* head);