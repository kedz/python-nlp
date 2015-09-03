CC = gcc
CFLAGS = -g -Wall -shared -fPIC -std=c11 -O9

.PHONY: default all clean

all: obj/document.o obj/mem_manager.o obj/tokenizer.o obj/tokenizer_utils.o
	
#obj/MurmurHash3.o 
#	#obj/tokenizer.o 

obj/document.o: src/document.c 
	$(CC) $(CFLAGS) -c src/document.c -o obj/document.o

obj/tokenizer.o: src/tokenizer.c 
	$(CC) $(CFLAGS) -c src/tokenizer.c -o obj/tokenizer.o

obj/tokenizer_utils.o: src/tokenizer_utils.c
	$(CC) $(CFLAGS) -c src/tokenizer_utils.c -o obj/tokenizer_utils.o

src/tokenizer.c:
	cd src; ragel tokenizer.rl

src/tokenizer_utils.c:
	cd src; ragel tokenizer_utils.rl

#obj/MurmurHash3.o:
#	$(CC) $(CFLAGS) -c src/MurmurHash3.c -o obj/MurmurHash3.o

obj/mem_manager.o:
	$(CC) $(CFLAGS) -c src/mem_manager.c -o obj/mem_manager.o


clean:
	rm -rf obj/
	rm -f src/tokenizer.c
	rm -f src/tokenizer_utils.c
