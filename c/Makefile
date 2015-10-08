CC = gcc
CFLAGS = -g -Wall -shared -fPIC -std=c11 #-O9
INCLUDE = -I../include/

.PHONY: clean ragel

all: obj obj/MurmurHash3.o obj/mem_manager.o obj/annotations.o \
	tokenizer util

obj:
	mkdir -p obj; mkdir -p obj/tokenizer; mkdir -p obj/util;

util: obj/util/conll_reader.o

obj/util/conll_reader.o: src/util/conll_reader.c
	$(CC) $(CFLAGS) -c src/util/conll_reader.c -o obj/util/conll_reader.o \
		$(INCLUDE)

src/util/conll_reader.c: src/util/conll_reader.rl
	cd src/util; ragel conll_reader.rl


obj/MurmurHash3.o: src/MurmurHash3.c
	$(CC) $(CFLAGS) -c src/MurmurHash3.c -o obj/MurmurHash3.o $(INCLUDE)

obj/mem_manager.o: src/mem_manager.c
	$(CC) $(CFLAGS) -c src/mem_manager.c -o obj/mem_manager.o $(INCLUDE)

obj/annotations.o: src/annotations.c
	$(CC) $(CFLAGS) -c src/annotations.c -o obj/annotations.o $(INCLUDE)

ragel: src/tokenizer_utils.c src/tokenizer.c \
	src/tokenizer/whitespace_tokenizer.c

src/tokenizer_utils.c: src/tokenizer_utils.rl
	cd src; ragel tokenizer_utils.rl

src/tokenizer.c: src/tokenizer.rl
	cd src; ragel tokenizer.rl

src/tokenizer/whitespace_tokenizer.c: src/tokenizer/whitespace_tokenizer.rl
	cd src/tokenizer; ragel whitespace_tokenizer.rl

tokenizer: obj/tokenizer_utils.o obj/tokenizer.o \
	obj/tokenizer/whitespace_tokenizer.o obj/tokenizer/sentence_tokenizer.o

obj/tokenizer_utils.o: src/tokenizer_utils.c
	$(CC) $(CFLAGS) -c src/tokenizer_utils.c -o obj/tokenizer_utils.o $(INCLUDE)

obj/tokenizer.o: src/tokenizer.c
	$(CC) $(CFLAGS) -c src/tokenizer.c -o obj/tokenizer.o $(INCLUDE)

obj/tokenizer/whitespace_tokenizer.o: src/tokenizer/whitespace_tokenizer.c
	$(CC) $(CFLAGS) -c src/tokenizer/whitespace_tokenizer.c -o obj/tokenizer/whitespace_tokenizer.o $(INCLUDE)

obj/tokenizer/sentence_tokenizer.o: src/tokenizer/sentence_tokenizer.c
	$(CC) $(CFLAGS) -c src/tokenizer/sentence_tokenizer.c -o obj/tokenizer/sentence_tokenizer.o $(INCLUDE)

clean:
	rm -rf obj/
