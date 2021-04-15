.DEFAULT_TARGET:=mainP
.PHONY: all clean
CC= gcc

$? #Special command for exiting if error found

all: clean mainP main.o calcsum.o

mainP: calcsum.o main.o
	@echo "Final Compile"
	#sleep 1
	${CC} main.o calcsum.o -o $@
main.o:
	@echo "Compiling Main object"
	#sleep 1
	 ${CC} -O1 -Wall -Wextra -c main.c -o $@
calcsum.o: 
	@echo "Compiling Calcsum Lib"
	#sleep 1
	${CC} -O1 -Wall -Wextra -c calcsum.c -o $@
clean: 
	rm -f main.o calcsum.o
