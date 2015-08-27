CC = gcc
CFLAGS = -g -Wall -shared -fPIC -std=c11 -O9

.PHONY: default all clean c annotators include
all: lib/nlp.so

lib/nlp.so: c annotators include
	mkdir -p lib;
	$(CC) $(CFLAGS) -Wl,-soname,libnlp.so -o lib/libnlp.so c/obj/*.o;

include:
	mkdir -p include/nlp; cp c/src/*.h include/nlp/;

c:
	cd c; mkdir -p obj; make;

clean:
	cd c; make clean;
	rm -rf include;
	rm -rf lib;
