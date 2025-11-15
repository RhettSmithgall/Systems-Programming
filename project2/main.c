#include "headers.h"

/*
a 2 pass sic assembler!
takes a file of sic assembly code and create an object code file
*/
int main( int argc, char* argv[]){
    if ( argc !=2 ) {                               //check for the right amount of command-line arguments 
        printf("%sERROR:%s USAGE is %s <filename>\n",KRED,KNRM, argv[0] );
        return -1; 
	}

    if(strcmp(argv[1],"-a") == 0){
	autograph();
	return 0;
    }

    FILE *fp;
	fp = fopen( argv[1], "r"  );                    //try and open the file
	if ( fp == NULL ) {
		printf("%sERROR:%s file %s not found\n",KRED,KNRM,argv[1]);
        fclose(fp);
		return -1;
	}

    char msg[1024]; //for errors

    //variables for reading 
    char readLine[1024]; 
    int lineNum = 1;

    struct symbol* SYMTAB = NULL; //declare a pointer to a symbol table
    int address = 0x0;

    char progName[7] = "";
    int start = 0;
    int end = 0;

    int seenStart = 0;

	while( fgets(readLine, 1023, fp) != NULL   ){       //read the file line by line
        if (readLine[0] == '#'   ) {                    //comment line
            lineNum++;
            continue;	
        }

        if (isBlank(readLine)) {               //blank lines are not allowed
            printf("%sERROR:%s Blank line found at line %d\n",KRED,KNRM, lineNum);
            fclose(fp);
            return -1;
        }

        wordStruct* word = getWord(readLine);

        if(seenStart == 0){ //if we haven't seen start yet
            if(strcmp(word->instruction, "START") == 0){ //check the line
                seenStart = 1; //if its there, great!
            }
            else{ //if not, error :(
                printf("%sERROR:%s Expected a START directive at line %d\n",KRED,KNRM,lineNum);
                return -1;
                }
        }
        
        //this block checks the symbol token and makes sure it follows the rules
        if(word->symbol[0] != '\0'){
	    int i = symbolExists(SYMTAB,word->symbol);
            if(i > 0) {   //see if the symbol is already defined  
            snprintf(msg, sizeof(msg), "Symbol %s was already defined on line %d", word->symbol, i); 
            error(argv[1],readLine,word,msg,lineNum,word->symcol);
            fclose(fp);
            return -1;
            }

            if(isDirective(word->symbol) || isOpcode(word->symbol)){
            snprintf(msg, sizeof(msg), "Symbol %s is a SIC assembly reserved instruction name", word->symbol); 
            error(argv[1],readLine,word,msg,lineNum,word->symcol);
            fclose(fp);
            return -1;
            }

            if (!isalpha(word->symbol[0])) { // Check if first character is A-Z
            snprintf(msg, sizeof(msg), "Character %c at the begining of symbol %s is not A-Z",word->symbol[0],word->symbol); 
            error(argv[1],readLine,word,msg,lineNum,word->symcol);
            fclose(fp);
            return -1;
            }

            if (strlen(word->symbol) > 6) { // Check length <= 6
            snprintf(msg, sizeof(msg), "Symbol %s is longer than 6 characters",word->symbol); 
            error(argv[1],readLine,word,msg,lineNum,word->symcol);
            fclose(fp);
            return -1;
            }

            for (int i = 0; word->symbol[i] != '\0'; i++) { // Check for forbidden characters
            if (strchr(",$!=+-()@", word->symbol[i]) != NULL) {
                snprintf(msg, sizeof(msg), "Invalid character %c in symbol %s",word->symbol[i],word->symbol); 
                error(argv[1],readLine,word,msg,lineNum,word->symcol+i+1);
                fclose(fp);
                return -1;
            }
            }
        }

        if(strcmp(word->instruction, "START") == 0) {      
            address = strtol(word->operand, NULL, 16);
            strcpy(progName,word->symbol);
            start = address;
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
                error(argv[1],readLine,word,msg,lineNum,word->opcol + i);
                fclose(fp);
                return -1;
            }
            address += ceil(strlen(numbytes)/2.0); 
            }
        }
        else if(strcmp(word->instruction, "WORD") == 0) {  
            if(strtol(word->operand, NULL, 10) > 0x7FFFFF){
            snprintf(msg, sizeof(msg), "Operand %s exceeds 24 bit word limit",word->operand); 
            error(argv[1],readLine,word,msg,lineNum,word->opcol);
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
        else if(strcmp(word->instruction, "END") == 0) {  
            end = address;      
            address += 3; 
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
        printf("%sERROR:%s Program too large. Max size is 32767 bytes.\n",KRED,KNRM);
        fclose(fp);
        return -1;
    }

    rewind(fp);

    char recordLine[128]; //the line we build the record on!

    char objCode[70] = "";
    address = start;
    int mods[1024];
    int j = 0;

    int fei = -1; //FIRST EXECUTABLE INSTRUCTION

    char buffer[80] = "";


    snprintf(buffer,sizeof(buffer),"%s.obj",argv[1]); 
    FILE *fpout = fopen(buffer, "w");

    struct record* OPTAB = NULL; //declare a pointer to a record table

    snprintf(recordLine,sizeof(recordLine),"H%-7s%06X%06X\n",progName, start, end - start);
    insertRecord(&OPTAB,recordLine);
    recordLine[0] = '\0';

    lineNum = 1;
    while( fgets(readLine, 1023, fp) != NULL   ){       //read the file line by line
        if (readLine[0] == '#'   ) {                   //comment line
            lineNum++;
            continue;	
        }

        wordStruct* word = getWord(readLine);

        if(fei == -1){
            if(isDirective(word->instruction) == 0){ //isDirective returns 0 on false, dont even start, i know
                fei = address;
            }
        }

        if(isDirective(word->instruction)){
            if(strcmp(word->instruction, "START") == 0) {   
                lineNum++;   
                address = start;
                continue;
            }
            else if(strcmp(word->instruction, "BYTE") == 0) {   
                char numbytes[64] = {0};     
                if(word->operand[0] == 'C') {            
                    sscanf(word->operand, "C'%[^']'", numbytes); //remove C'__'

                    for(int i = 0;numbytes[i] != '\0';i++){ //go through each character in the string, convert to ascii and print
                        if(strlen(objCode) == 60){ //if there is no more room in the text record, make a new one
                            snprintf(buffer,sizeof(buffer),"%02X%s\n",(int)strlen(objCode)/2,objCode);
                            strcat(recordLine,buffer);
                            insertRecord(&OPTAB,recordLine);
                            recordLine[0] = '\0';
                            objCode[0] = '\0';
                        } //if no text record exists, start one
                        if(objCode[0] == '\0'){
                            snprintf(buffer, sizeof(buffer),"T%06X",address);
                            strcat(recordLine,buffer);
                        }
                        snprintf(buffer, sizeof(buffer), "%X",numbytes[i]); 
                        int num = (int)strtol(buffer, NULL, 16);
                        snprintf(buffer, sizeof(buffer), "%X",IBM2ISO(num)); 
                        strcat(objCode,buffer);
                        address++;
                    }
                }
                else if(word->operand[0] == 'X'){    
                    sscanf(word->operand, "X'%[^']'", numbytes); //remove X'__'

                    for(int i = 0;numbytes[i] != '\0';i++){
                        if(strlen(objCode) == 60){
                            snprintf(buffer,sizeof(buffer),"%02X%s\n",(int)strlen(objCode)/2,objCode);
                            strcat(recordLine,buffer);
                            insertRecord(&OPTAB,recordLine);
                            recordLine[0] = '\0';
                            objCode[0] = '\0';
                        } 
                        if(objCode[0] == '\0'){
                            snprintf(buffer,sizeof(buffer),"T%06X",address);
                            strcat(recordLine,buffer);
                        }
                        snprintf(buffer, sizeof(buffer), "%c",numbytes[i]); 
                        strcat(objCode,buffer);
                        if(i%2 == 0){ //every 2 numbers is a byte
                            address++;
                        }
                    }
                }
                }
                else if(strcmp(word->instruction, "RESB") == 0) {  //RESB always ends a text record
                    if(strlen(objCode)>0){ //if there is anything in the buffer, print it and end the text record
                        snprintf(buffer,sizeof(buffer),"%02X%s\n",(int)strlen(objCode)/2,objCode);
                        strcat(recordLine,buffer);
                        insertRecord(&OPTAB,recordLine);
                        recordLine[0] = '\0';
                        objCode[0] = '\0'; 
                    }
                    address += strtol(word->operand, NULL, 10); 
                }
                else if(strcmp(word->instruction, "RESW") == 0) {  //RESW, like its brother, also ends text records
                    if(strlen(objCode)>0){ //if there is anything in the buffer, print it and end the text record
                        snprintf(buffer,sizeof(buffer),"%02X%s\n",(int)strlen(objCode)/2,objCode);
                        strcat(recordLine,buffer);
                        insertRecord(&OPTAB,recordLine);
                        recordLine[0] = '\0';
                        objCode[0] = '\0';     
                    }
                    address += 3 * strtol(word->operand, NULL, 10); 
                }
                else if(strcmp(word->instruction, "WORD") == 0) {  
                    if(60 - strlen(objCode) < 6){
                        snprintf(buffer,sizeof(buffer),"%02X%s\n",(int)strlen(objCode)/2,objCode);
                        strcat(recordLine,buffer);
                        insertRecord(&OPTAB,recordLine);
                        recordLine[0] = '\0';
                        objCode[0] = '\0';   
                    }
                    if(objCode[0] == '\0'){
                        snprintf(buffer, sizeof(buffer),"T%06X",address);
                        strcat(recordLine,buffer);
                    }
                    snprintf(buffer, sizeof(buffer), "%06X",atoi(word->operand)); 
                    strcat(objCode,buffer);
                    address += 3;
                }
                else if(strcmp(word->instruction, "END") == 0){
                    if(symbolExists(SYMTAB,word->operand) == 0){ 
                        char str[9];                        
                        strcpy(str,word->operand); 
                        printf("%sDid you mean \"%s\"?%s\n",KBLU,spellchecker(str,SYMTAB)->name,KNRM);
                        snprintf(msg, sizeof(msg), "Operand %s on was never defined",word->operand); 
                        error(argv[1],readLine,word,msg,lineNum,word->opcol);
                        fclose(fp);
                        return -1;
                    }
                }
            lineNum++;
            continue;
        }

        if(60 - strlen(objCode) < 6){ //if there isn't enough room left in the buffer for another record, end the record
            snprintf(buffer,sizeof(buffer),"%02X%s\n",(int)strlen(objCode)/2,objCode);
            strcat(recordLine,buffer);
            insertRecord(&OPTAB,recordLine);
            recordLine[0] = '\0';
            objCode[0] = '\0';
        }

        
        if(objCode[0] == '\0'){
            snprintf(buffer, sizeof(buffer),"T%06X",address);
            strcat(recordLine,buffer);
        }
        
        if (strchr(word->operand, ',') != NULL) {
            char* token = strtok(word->operand,",");

            if(symbolExists(SYMTAB,token) == 0  && word->operand[0] != '\0'){ //if the symbol being used isn't defined
                char str[9];                        
                strcpy(str,word->operand); 
                printf("%sDid you mean \"%s\"?%s\n",KBLU,spellchecker(str,SYMTAB)->name,KNRM);
                snprintf(msg, sizeof(msg), "Operand %s on was never defined",token); 
                error(argv[1],readLine,word,msg,lineNum,word->opcol);
                fclose(fp);
                return -1;
            }

            snprintf(buffer, sizeof(buffer), "%02X",toOpcode(word->instruction)); 
            strcat(objCode,buffer);

            int addr = getSymbolAddress(SYMTAB,token);
            addr ^= 0x8000;
            snprintf(buffer, sizeof(buffer), "%04X",addr); 
            strcat(objCode,buffer);

            if(symbolExists(SYMTAB,token)){ //make a mod record
                mods[j] = address;
                j++; 
            }
        } 
        else 
        {
            if(symbolExists(SYMTAB,word->operand) == 0 && word->operand[0] != '\0'){ //if the symbol being used isn't defined
                char str[9];                         //^^^ could probably get rid of, in theory symbolExists will say false to '\0', right? 
                strcpy(str,word->operand); 

                printf("%sDid you mean \"%s\"?%s\n",KBLU,spellchecker(str,SYMTAB)->name,KNRM);

                snprintf(msg, sizeof(msg), "Operand %s on was never defined",word->operand); 
                error(argv[1],readLine,word,msg,lineNum,word->opcol);
                fclose(fp);
                return -1;
            }

            snprintf(buffer, sizeof(buffer), "%02X",toOpcode(word->instruction)); 
            strcat(objCode,buffer);

            snprintf(buffer, sizeof(buffer), "%04X",getSymbolAddress(SYMTAB,word->operand)); 
            strcat(objCode,buffer);

            if(symbolExists(SYMTAB,word->operand)){ 
                mods[j] = address;
                j++; 
            }
        }

        address += 3;
        lineNum++;
    }
    if(strlen(objCode) > 0){
        if(objCode[0] == '\0'){
            snprintf(buffer, sizeof(buffer),"T%06X",address);
            strcat(recordLine,buffer);
        }
        snprintf(buffer,sizeof(buffer),"%02X%s\n",(int)strlen(objCode)/2,objCode);
        strcat(recordLine,buffer);
        insertRecord(&OPTAB,recordLine);
    }

    for(int i = 0;i<j;i++){
        snprintf(recordLine,sizeof(recordLine),"M%06X04+%s\n",mods[i]+1,progName);
        insertRecord(&OPTAB,recordLine);
        recordLine[0] = '\0';
    }


    snprintf(recordLine,sizeof(recordLine),"E%06X\n",fei);
    insertRecord(&OPTAB,recordLine);

    //printRecords(OPTAB);
    
    fprintRecords(fpout,OPTAB);

    destroyRecords(OPTAB);
    
    //printSymbols(SYMTAB);

    destroySymbolTable(SYMTAB); 
}



