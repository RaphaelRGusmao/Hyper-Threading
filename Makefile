################################################################################
#                                IME-USP (2018)                                #
#           MAC0219 - Programacao Concorrente e Paralela - Desafio2            #
#                                                                              #
#                                   Makefile                                   #
#                                                                              #
#                       Marcelo Schmitt   - NUSP 9297641                       #
#                       Raphael R. Gusmao - NUSP 9778561                       #
################################################################################

.PHONY: clean
CC = gcc
#CFLAGS = -Wall -O2 -g
CFLAGS = -O2 -g
OBJS = \
	worker.o \
	desafio2.o

all: desafio2

desafio2: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lpthread
	#make clean

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *~
	rm -f desafio2

run:
	./desafio2

################################################################################
