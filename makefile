project1: main.o printSymbol.o InsertSymbol.o error.o isValidSymbolName.o destroySymbolTable.o \
          symbolExists.o createSymbol.o isOpcode.o isDirective.o isValidHex.o isBlank.o getWord.o autograph.o
	xlc -q64 -o project1 main.o printSymbol.o InsertSymbol.o error.o isValidSymbolName.o \
          destroySymbolTable.o symbolExists.o createSymbol.o isOpcode.o isDirective.o isValidHex.o \
           isBlank.o getWord.o autograph.o

main.o: main.c headers.h
	xlc -q64 -c -g main.c

autograph.o: autograph.c headers.h
	xlc -q64 -c -g autograph.c

getWord.o: getWord.c headers.h
	xlc -q64 -g getWord.c

printSymbol.o: printSymbol.c headers.h
	xlc -q64 -c -g printSymbol.c

InsertSymbol.o: InsertSymbol.c headers.h
	xlc -q64 -c -g InsertSymbol.c

error.o: error.c headers.h
	xlc -q64 -c -g error.c

isValidSymbolName.o: isValidSymbolName.c headers.h
	xlc -q64 -c -g isValidSymbolName.c

destroySymbolTable.o: destroySymbolTable.c headers.h
	xlc -q64 -c -g destroySymbolTable.c

symbolExists.o: symbolExists.c headers.h
	xlc -q64 -c -g symbolExists.c

createSymbol.o: createSymbol.c headers.h
	xlc -q64 -c -g createSymbol.c

isOpcode.o: isOpcode.c headers.h
	xlc -q64 -c -g isOpcode.c

isDirective.o: isDirective.c headers.h
	xlc -q64 -c -g isDirective.c

isValidHex.o: isValidHex.c headers.h
	xlc -q64 -c -g isValidHex.c

isBlank.o: isBlank.c headers.h
	xlc -q64 -c -g isBlank.c

clean:
	rm -f *.o project1
	rm -f *.dbg project1
