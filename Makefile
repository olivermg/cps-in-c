CC = clang

.PHONY: clean

main: main.o
	$(CC) -Wall -g -o $@ $<

%.o: %.c
	$(CC) -Wall -g -o $@ -c $<

clean:
	rm -vf *.o main

