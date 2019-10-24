CC=gcc
FLAGS=-Wall -g 
LIBS=-lpthread -ltermbox
OUT=lineracer
INCLUDE=-I headers/
OBJS=./out/linepieces.o ./out/bike.o 

$(OUT): ./out $(OBJS) ./out/main.o
	$(CC) $(FLAGS) $(LIBS) $(INCLUDE) -o $(OUT) ./out/main.o $(OBJS) 

./out:
	mkdir ./out

./out/main.o: main.c headers/main.h headers/constants.h $(OBJS)
	$(CC) $(FLAGS) $(INCLUDE) -o ./out/main.o -c main.c 
	
./out/bike.o: bike.c headers/bike.h
	$(CC) $(FLAGS) $(INCLUDE) -o ./out/bike.o -c bike.c

./out/linepieces.o: linepieces.c headers/linepieces.h
	$(CC) $(FLAGS) $(INCLUDE) -o ./out/linepieces.o -c linepieces.c

.Phony: run

run:
	./$(OUT)

clean:
	rm $(OUT) out/*
