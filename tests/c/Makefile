CC = gcc
CFLAGS = -g -Wall -std=c11 
INCLUDE = -I../../include
LIBS = -L../../lib -lnlp -lm
#TEST_SRC = memmgr_test.c  tokenizer_utils_tests.c tokenizer_tests.c \
		   sent_tok_tests.c ptb_inputs_test.c ws_tokenizer_tests.c
TEST_SRC = tokenizer_tests.c ws_tokenizer_tests.c ptb_inputs_test.c


all: test-libnlp sizes large_test

test-libnlp: test-libnlp.c $(TEST_SRC)
	$(CC) $(CFLAGS) test-libnlp.c $(TEST_SRC) -o test-libnlp $(INCLUDE) \
		$(LIBS)

large_test: large_test.c
	$(CC) $(CFLAGS) large_test.c -o large_test $(INCLUDE) $(LIBS);

sizes: sizes.c
	$(CC) $(CFLAGS) sizes.c -o sizes $(INCLUDE) $(LIBS)

#var_alloc_test:
#	$(CC) $(CFLAGS) var_allocation_timings.c -o var_alloc_test \
#		$(INCLUDE) $(LIBS)

clean:
	rm -f test-libnlp sizes large_test
