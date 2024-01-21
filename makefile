CC = gcc
CFLAGS = -Wall

all: tp

tp: main.c tp.c
	$(CC) $(CFLAGS) -o tp main.c tp.c

run: tp
	./tp $(ARGS)
	rm -f tp

test_c: test.c tp.c
	$(CC) $(CFLAGS) -o test_c test.c tp.c
	./test_c
	rm -f test_c

test_py: test.py
	python -m pytest test.py


