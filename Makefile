all: game mapper

DATA_FILES = $(wildcard data/*.x)

CFLAGS += --std=gnu99

data.o: data.c data.x data.h $(DATA_FILES)
	gcc -c -o data.o data.c

generate_nodes: generate_nodes.c data.o data.h
	gcc $(CFLAGS) -o generate_nodes generate_nodes.c

mapnodes.h: generate_nodes
	./generate_nodes > mapnodes.h

game: game.c proc.h proc.c animation.h animation.c resource.c resource.h maptree.c maptree.h mapnodes.h nos.c nos.h data.o data.h
	gcc $(CFLAGS) -o game game.c proc.c animation.c resource.c nos.c data.o -lm -g -lpthread -lGL

mapper: mapper.c nos.c nos.h data.o data.h
	gcc $(CFLAGS) -o mapper mapper.c nos.c data.o -lm -g -lpthread -lGL

clean:
	rm game
	rm mapper
	rm mapnodes.h
	rm generate_nodes

