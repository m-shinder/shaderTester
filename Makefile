CC = gcc
NAME = shaderTester
CCFLAGS = `pkg-config --cflags gtk+-3.0 --libs epoxy` -rdynamic

all: bin/main.o bin/glarea-functions.o bin/ui-window-functions.o
	$(CC) bin/*.o -o $(NAME) $(CCFLAGS) 

bin/main.o: src/main.c
	$(CC) -c src/main.c -o bin/main.o $(CCFLAGS)

bin/ui-window-functions.o: src/ui-window-functions.c
	$(CC) -c src/ui-window-functions.c -o bin/ui-window-functions.o $(CCFLAGS)

bin/glarea-functions.o: src/glarea-functions.c
	$(CC) $(CCFLAGS) -c src/glarea-functions.c -o bin/glarea-functions.o

clean:
	rm $(NAME) bin/*
