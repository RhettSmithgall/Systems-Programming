#include "headers.h"

int main( int argc, char* argv[]){

    if ( argc !=2 ) {                               //make sure the program has the right number of arguments
        printf("ERROR: USAGE is %s <filename>\n", argv[0] );
        return -1; 
	}

    FILE *fp;
	fp = fopen( argv[1], "r"  );                    //try and open the file
	if ( fp == NULL ) {
		printf("Error: file not found\n", argv[1]);
		return -1;
	}

    struct symbol* SYMTAB = NULL; //declare a pointer to a symbol table

    char line[1024]; 

    int lineCount = 0;    
    int address = 0x0; 
    char* token;
    char* symName;
    
    //line counter
	while( fgets(line, 1023, fp) != NULL   ){       //read the file line by line
        if ( line[0] == '#'   ) {                   //comment line
            lineCount++;
            continue;	
        }

        if ( line[0] == '\n'      ) {               //blank lines are not allowed
            printf("ERROR: Blank line found at line %d\n", lineCount);
            fclose(fp);
            return -1;
        }

        token = strtok(line, " \n\t\r");      //tokenize the line

        
        if(isDirective(token) || isOpcode(token)) {    
            token = strtok(NULL, " \n\t\r");  
            
            if(token != NULL){
                if(isDirective(token) || isOpcode(token)) { 
                    printf("Error: Symbol name %s at line %d is a SIC assembly reserved instruction name\n", token, lineCount);
                    return -1;
                }
            }
            lineCount++;
            address += 3;
            continue;
        }     
 
                           
        if(symbolExists(SYMTAB, token)) {     
            printf("Error: Symbol %s at line %d was already defined\n", token, lineCount);
            return -1;
        }

        if(!isValidSymbolName(token)){
            printf("Error: invalid symbol name %s at line %d\n", token, lineCount);
            return -1;
        }

        symName = token;

        token = strtok(NULL, " \n\t\r");   
        if(isDirective(token)) { 
                if(strcmp(token, "START") == 0) {      
                    token = strtok(NULL, " \n\t\r");   
                    address = strtol(token, NULL, 16);
                    lineCount++;   
                    continue;
                }

            if(strcmp(token, "END") == 0) { 
                    address += 3;   
                    lineCount++;   
                    continue;    
                }

            if(strcmp(token, "BYTE") == 0) {       
                token = strtok(NULL, " \n\t\r");   
                if(token[0] == 'C') {            
                    sscanf(token, "C'%[^']'", token); //remove C'__'
                    if(strlen(token) > 3){
                        printf("ERROR: Constant %s exceeds 24 bits at line %d\n",token,lineCount);
                        fclose(fp);
                        return -1;
                    }
                    address += strlen(token);
                    lineCount++;   
                    continue;
                }
                else if(token[0] == 'X'){    
                    sscanf(token, "X'%[^']'", token); //remove X'__'
                    if (!(isValidHex(token))) //valid hex characters
                    {
                        printf("ERROR: invalid hex %s at line %d\n",token,lineCount);
                        fclose(fp);
                        return -1;
                    }
                    if(strtol(token, NULL, 16) > 0x7FFFFF){
                        printf("ERROR: Constant %s exceeds 24 bits at line %d\n",token,lineCount);
                        fclose(fp);
                        return -1;
                    }
                    address += ceil(strlen(token)/2.0);
                    lineCount++;   
                    continue;
                }
            }

            if(strcmp(token, "WORD") == 0) {  
                token = strtok(NULL, " \n\t\r");  
                if(atoi(token) > 0x7FFFFF){
                    printf("ERROR: Constant %s exceeds 24 bits at line %d\n",token,lineCount);
                    fclose(fp);
                    return -1;
                }     
                address += 3; 
                lineCount++;   
                continue;
            }

            if(strcmp(token, "RESB") == 0) {  
                token = strtok(NULL, " \n\t\r");  
                address += strtol(token, NULL, 10); 
                lineCount++;   
                continue;
            }

            if(strcmp(token, "RESW") == 0) {       
                token = strtok(NULL, " \n\t\r");   
                address += 3 * strtol(token, NULL, 10); 
                lineCount++;   
                continue;
            }

            if(strcmp(token, "RESR") == 0) {       
                address += 3; 
                lineCount++;   
                continue;
            }

            if(strcmp(token, "EXPORTS") == 0) {    
                address += 3; 
                lineCount++;   
                continue;
            }   
        }

        struct symbol* currSym = insertSymbol(&SYMTAB, symName, address, lineCount);
        lineCount++;   
        address += 3;
    }
    if(address > 0x8000){
        printf("ERROR: Program too large. Max size is 32767 bytes.\n");
        fclose(fp);
        return -1;
    }

    printSymbols(SYMTAB);                      

    fclose(fp);
    return 0;
}