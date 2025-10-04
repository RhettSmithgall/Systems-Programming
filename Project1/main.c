#include "headers.h"

int main( int argc, char* argv[]){
    if ( argc !=2 ) {                               //check for the right amount of command-line arguments 
        printf("ERROR: USAGE is %s <filename>\n", argv[0] );
        return -1; 
	}

    FILE *fp;
	fp = fopen( argv[1], "r"  );                    //try and open the file
	if ( fp == NULL ) {
		printf("Error: file %s not found\n",argv[1]);
        fclose(fp);
		return -1;
	}

    char msg[1024]; //for errors
    char forbidden[] = ",$!=+-()@"; //for symbol validation

    //variables for reading 
    char readLine[1024]; 
    int lineNum = 1;


    struct symbol* SYMTAB = NULL; //declare a pointer to a symbol table
    int address = 0x0;

	while( fgets(readLine, 1023, fp) != NULL   ){       //read the file line by line
        if (readLine[0] == '#'   ) {                    //comment line
            lineNum++;
            continue;	
        }

        if (isBlank(readLine)) {               //blank lines are not allowed
            printf("ERROR: Blank line found at line %d\n", lineNum);
            fclose(fp);
            return -1;
        }

        wordStruct* word = getWord(readLine);
        //printf("Symbol:%s\tDirective:%s\tOperand:%s\n",word->symbol,word->instruction,word->operand);

        //this block checks the symbol token and makes sure it follows the rules
        if(word->symbol[0] != '\0'){
            if(symbolExists(SYMTAB, word->symbol)) {   //see if the symbol is already defined  
            snprintf(msg, sizeof(msg), "Duplicate symbol %s", word->symbol); 
            error(word,msg,lineNum,word->symcol);
            fclose(fp);
            return -1;
            }

            if(isDirective(word->symbol) || isOpcode(word->symbol)){
            snprintf(msg, sizeof(msg), "Symbol %s is a SIC assembly reserved instruction name", word->symbol); 
            error(word,msg,lineNum,word->symcol);
            fclose(fp);
            return -1;
            }

            if (!isalpha(word->symbol[0])) { // Check if first character is A-Z
            snprintf(msg, sizeof(msg), "Character %c at the begining of symbol %s is not A-Z",word->symbol[0],word->symbol); 
            error(word,msg,lineNum,word->symcol);
            fclose(fp);
            return -1;
            }

            if (strlen(word->symbol) > 6) { // Check length <= 6
            snprintf(msg, sizeof(msg), "Symbol %s is longer than 6 characters",word->symbol); 
            error(word,msg,lineNum,word->symcol);
            fclose(fp);
            return -1;
            }

            for (int i = 0; word->symbol[i] != '\0'; i++) { // Check for forbidden characters
            if (strchr(",$!=+-()@", word->symbol[i]) != NULL) {
                snprintf(msg, sizeof(msg), "Invalid character %c in symbol %s",word->symbol[i],word->symbol); 
                error(word,msg,lineNum,word->symcol+i+1);
                fclose(fp);
                return -1;
            }
            }
        }

        if(strcmp(word->instruction, "START") == 0) {      
            address = strtol(word->operand, NULL, 16);
        }

        if(word->symbol[0] != '\0'){
            insertSymbol(&SYMTAB,word->symbol,address,lineNum);
        }

        //this block validates directives and their operands 
        if(strcmp(word->instruction, "BYTE") == 0) {   
            char numbytes[64] = {0};     
            if(word->operand[0] == 'C') {            
            sscanf(word->operand, "C'%[^']'", numbytes); //remove C'__'
            address += strlen(numbytes); 
            }
            else if(word->operand[0] == 'X'){    
            sscanf(word->operand, "X'%[^']'", numbytes); //remove X'__'
            int i = isValidHex(numbytes);
            if (i > 0) //valid hex characters
            {
                snprintf(msg, sizeof(msg), "Operand %s contains invalid hex character '%c'",word->operand,numbytes[i-1]); 
                error(word,msg,lineNum,word->opcol + i);
                fclose(fp);
                return -1;
            }
            address += ceil(strlen(numbytes)/2.0); 
            }
        }
        else if(strcmp(word->instruction, "WORD") == 0) {  
            if(strtol(word->operand, NULL, 10) > 0x7FFFFF){
            snprintf(msg, sizeof(msg), "Operand %s exceeds 24 bit word limit",word->operand); 
            error(word,msg,lineNum,word->opcol);
            fclose(fp);
            return -1;
            }     
            address += 3;
        }
        else if(strcmp(word->instruction, "RESB") == 0) {   
            address += strtol(word->operand, NULL, 10); 
        }
        else if(strcmp(word->instruction, "RESW") == 0) {        
            address += 3 * strtol(word->operand, NULL, 10); 
        }
        else{
            if(strcmp(word->instruction, "START") != 0){
            address += 3;
            }
        }
 
        lineNum++;
        
       free(word);
    }
    if(address > 0x8000){
        printf("ERROR: Program too large. Max size is 32767 bytes.\n");
        fclose(fp);
        return -1;
    }
    
    printSymbols(SYMTAB);

}




