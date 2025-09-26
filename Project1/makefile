project1: main.o printsymbols.o insertsymbol.o
	xlc -q64 -o project1 main.o printsymbols.o insertsymbol.o

main.o: main.c headers.h
	xlc -q64 -c -g main.c

printsymbols.o: printsymbols.c headers.h
	xlc -q64 -c -g printsymbols.c

insertsymbol.o: insertsymbol.c headers.h
	xlc -q64 -c -g insertsymbol.c
