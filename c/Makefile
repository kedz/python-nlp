CC = gcc
CFLAGS = -g -Wall -shared -fPIC -std=c99 -O4

.PHONY: default all clean

all: obj/mem_manager.o obj/MurmurHash3.o obj/document.o obj/tokenizer.o 

obj/document.o: src/document.c 
	$(CC) $(CFLAGS) -c src/document.c -o obj/document.o

obj/tokenizer.o: src/tokenizer.c 
	$(CC) $(CFLAGS) -c src/tokenizer.c -o obj/tokenizer.o

src/tokenizer.c:
	cd src; ragel tokenizer.rl

obj/MurmurHash3.o:
	$(CC) $(CFLAGS) -c src/MurmurHash3.c -o obj/MurmurHash3.o

obj/mem_manager.o:
	$(CC) $(CFLAGS) -c src/mem_manager.c -o obj/mem_manager.o


clean:
	rm -rf obj/
	rm src/tokenizer.c
