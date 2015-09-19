CC = gcc
CFLAGS = -g -Wall -std=c11 
INCLUDE = -I../../include
LIBS = -L../../lib -lnlp -lm
TEST_SRC = memmgr_test.c  tokenizer_utils_tests.c tokenizer_tests.c \
		   ptb_inputs_test.c

#all: test sizes var_alloc_test
all: test-libnlp sizes

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

#test_span: test_span.c
#	$(CC) $(CFLAGS) test_span.c -o test_span $(INCLUDE) $(LIBS)

#test_tokenizer: test_tokenizer.c
#	$(CC) $(CFLAGS) test_tokenizer.c -o test_tokenizer $(INCLUDE) $(LIBS)

#ptb_inputs_test: ptb_inputs_test.c
#	$(CC) $(CFLAGS) ptb_inputs_test.c -o ptb_inputs_test $(INCLUDE) $(LIBS)

#test: memmgr_test.c
#	$(CC) $(CFLAGS) memmgr_test.c -o test $(INCLUDE) $(LIBS)
clean:
	rm -f test-libnlp sizes
