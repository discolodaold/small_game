all: main

DATA_FILES = $(wildcard data/*.x)

CFLAGS += --std=gnu99

generate_nodes: generate_nodes.c data.c data.x $(DATA_FILES)
	gcc $(CFLAGS) -o generate_nodes generate_nodes.c

mapnodes.h: generate_nodes
	./generate_nodes > mapnodes.h

main: main.c sys.h sys.c proc.h proc.c animation.h animation.c resource.c resource.h maptree.c maptree.h mapnodes.h
	gcc $(CFLAGS) -o main main.c sys.c proc.c animation.c resource.c -lm -g -lpthread

