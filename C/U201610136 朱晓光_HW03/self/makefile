# simple makefile

main: first.c second.h second.c
	gcc -c first.c second.c
	ls -ahl first.o second.o

	gcc -o a.out first.o second.o second.h
	ls -ahl a.out
	
	rm first.o second.o
