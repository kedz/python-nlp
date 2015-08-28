cd ../fnlp-c
make clean;
make
cd ../test-c
make
LD_LIBRARY_PATH=/home/kedz/projects2015/fnlp/fnlp-c/lib/ ./test
