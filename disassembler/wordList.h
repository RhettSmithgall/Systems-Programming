//a struct for a SIC Assembly WORD
typedef struct wordStruct{
    char symbol[128];
    char instruction[128];
    char operand[128];
    struct wordStruct *next;
} wordStruct;

//function defintions
wordStruct* createWord(char* symbol,char* instruction,char* operand);
wordStruct* insertword(wordStruct** head, wordStruct* newWord);
void destroywords(wordStruct* head);
void fprintwords(FILE *fp,wordStruct* head);
void printwords(wordStruct* head);