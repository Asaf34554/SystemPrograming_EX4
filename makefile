CC = gcc
FLAGS = -Wall -g -fPIC


all: .graph edges.o node.o algo.o main.o

.graph: main.o algo.o edges.o node.o
	$(CC) $(FLAGS) main.o algo.o edges.o node.o -o.graph 
algo.o: algo.c node.h edges.h graph.h
	$(CC) $(FLAGS) -c algo.c
main.o: main.c graph.h node.h
	$(CC) $(FLAGS) -c main.c

node.o: node.c node.h graph.h
	$(CC) $(FLAGS) -c node.c
edges.o: edges.c edges.h node.h graph.h
	$(CC) $(FLAGS) -c edges.c





.PHONY: clean all
clean: 
	rm -f  *.o .graph 