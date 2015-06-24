CC=gcc

prutool: prutool.c
	$(CC) -g -o prutool -Wall prutool.c

clean:
	rm prutool
