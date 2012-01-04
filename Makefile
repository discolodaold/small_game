all: main

main: main.c sys.h sys.c proc.h proc.c animation.h animation.c resource.c resource.h
	gcc -o main main.c sys.c proc.c animation.c resource.c -lm -g -lpthread

