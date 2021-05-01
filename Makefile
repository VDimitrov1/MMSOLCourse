.DEFAULT_TARGET:=mainP
.PHONY: all clean
CC= gcc

$? #Special command for exiting if error found

all: clean mainP main.o

mainP:  main.o
	@echo "Final Compile"
	#sleep 1
	${CC} main.o -lpthread -o $@
main.o:
	@echo "Compiling Main object"
	#sleep 1
	 ${CC} -O1 -Wall -Wextra -c main.c -o $@
clean: 
	rm -f main.o 
