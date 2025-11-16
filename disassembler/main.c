#include "headers.h"

int main( int argc, char* argv[]){
    if ( argc !=2 ) {                               //check for the right amount of command-line arguments 
        printf("%sERROR:%s USAGE is %s <filename>\n",KRED,KNRM, argv[0] );
        return -1; 
	}

    char msg[1024]; //for errors

    FILE *fp;
	fp = fopen( argv[1], "r"  );                    //try and open the file
	if ( fp == NULL ) {
		printf("%sERROR:%s file %s not found\n",KRED,KNRM,argv[1]);
        fclose(fp);
		return -1;
	}

    //variables for reading 
    char readLine[1024]; 
    char buffer[32];
    char symName[12];

    wordStruct word;
    struct symbol* SYMTAB;
    int SymbolNumber = 1;

    while( fgets(readLine, 1023, fp) != NULL   ){       //read the file line by line
        if(readLine[0] == 'T'){ //T record
            char* i = readLine;
            i += 9; //jump to column 10 
            while(i[0] != '\0'){
                i += 2; //skip op codes
                strncpy(buffer,i,4);
                buffer[4] = '\0';
                if(symbolExists(SYMTAB,(int)strtol(buffer, NULL, 16))){
                    //nothing
                }
                else{
                    sprintf(symName,"sym%d",SymbolNumber);
                    insertSymbol(&SYMTAB,symName,(int)strtol(buffer, NULL, 16),0);
                    SymbolNumber++;
                }
                i += 4;
            }
        }
    }

    printSymbols(SYMTAB);

    rewind(fp);

    fgets(readLine, 1023, fp);
    int address = 0x0;

    if(readLine[0] == 'H'){
        strncpy(word.symbol,readLine + 1,7);
        strcpy(word.instruction,"START");
        strncpy(word.operand,readLine + 8,6);
        address = (int)strtol(word.operand, NULL, 16);

        printf("%s\t%s\t%X\n",word.symbol,word.instruction,address);
    }
    else{
        printf("ERROR: no h record");
    }
    word.symbol[0] = '\0';
    word.instruction[0] = '\0';
    word.operand[0] = '\0';

    while( fgets(readLine, 1023, fp) != NULL   ){       //read the file line by line
        if(readLine[0] == 'T'){ //T record
            strncpy(buffer,readLine + 1,6);
            address = (int)strtol(word.operand, NULL, 16);

            char* i = readLine;
            i += 9;
            //printf("%s",i);
            while(i[0] != '\0'){
                strncpy(buffer,i,2);
                buffer[2]='\0';
                i += 2;
                strcpy(word.instruction,toInstruction((int)strtol(buffer, NULL, 16)));
                strncpy(word.operand,i,4);
                word.operand[4] = '\0';
                i += 4;
                printf("%s\t%s\t%s\n",word.symbol,word.instruction,word.operand);
                word.symbol[0] = '\0';
                word.instruction[0] = '\0';
                word.operand[0] = '\0';
            }
        }
        else if(readLine[0] == 'M'){ //M record
            continue;
        }
        else{ //E record
            word.symbol[0] = '\0';
            strcpy(word.instruction,"END");
            strncpy(word.operand,readLine + 1,6);
            address = (int)strtol(word.operand, NULL, 16);
            printf("%s\t%s\t%X",word.symbol,word.instruction,address);
        }
    }

    fclose(fp);
}