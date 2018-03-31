CC=gcc

CFLAGS=-std=gnu11 -Wall -O0
LDFLAGS=-lreadline -pthread -lm

all: minidesafio2

run:
	./minidesafio2

clean:	
	rm -rf *.o *~
	rm -rf minidesafio2

minidesafio2: minidesafio2.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
