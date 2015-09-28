CC = gcc
CFLAGS = -g -Wall -shared -fPIC -std=c11 -O9

.PHONY: default all clean c include
all: lib/nlp.so

lib/nlp.so: c include
	mkdir -p lib;
	$(CC) $(CFLAGS) -Wl,-soname,libnlp.so -o lib/libnlp.so c/obj/*.o c/obj/tokenizer/*.o;

include:
	mkdir -p include/nlp; cp c/src/*.h include/nlp/;
	mkdir -p include/nlp/tokenizer; cp c/src/tokenizer/*.h include/nlp/tokenizer/;

c: include
	cd c; make

clean:
	cd c; make clean;
	rm -rf include;
	rm -rf lib;
