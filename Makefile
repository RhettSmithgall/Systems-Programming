project1: main.o printSymbol.o InsertSymbol.o error.o isValidSymbolName.o \
          destroySymbolTable.o symbolExists.o createSymbol.o isOpcode.o \
          isDirective.o isValidHex.o isBlank.o getWord.o autograph.o
	gcc -Wall -g -o project1 main.o printSymbol.o InsertSymbol.o error.o \
          isValidSymbolName.o destroySymbolTable.o symbolExists.o createSymbol.o \
          isOpcode.o isDirective.o isValidHex.o isBlank.o getWord.o autograph.o

main.o: main.c headers.h
	gcc -Wall -g -c main.c

autograph.o: autograph.c headers.h
	gcc -Wall -g -c autograph.c

getWord.o: getWord.c headers.h
	gcc -Wall -g -c getWord.c

printSymbol.o: printSymbol.c headers.h
	gcc -Wall -g -c printSymbol.c

InsertSymbol.o: InsertSymbol.c headers.h
	gcc -Wall -g -c InsertSymbol.c

error.o: error.c headers.h
	gcc -Wall -g -c error.c

isValidSymbolName.o: isValidSymbolName.c headers.h
	gcc -Wall -g -c isValidSymbolName.c

destroySymbolTable.o: destroySymbolTable.c headers.h
	gcc -Wall -g -c destroySymbolTable.c

symbolExists.o: symbolExists.c headers.h
	gcc -Wall -g -c symbolExists.c

createSymbol.o: createSymbol.c headers.h
	gcc -Wall -g -c createSymbol.c

isOpcode.o: isOpcode.c headers.h
	gcc -Wall -g -c isOpcode.c

isDirective.o: isDirective.c headers.h
	gcc -Wall -g -c isDirective.c

isValidHex.o: isValidHex.c headers.h
	gcc -Wall -g -c isValidHex.c

isBlank.o: isBlank.c headers.h
	gcc -Wall -g -c isBlank.c

clean:
	rm -f *.o project1.exe

