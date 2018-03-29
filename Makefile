################################################################################
#                                IME-USP (2018)                                #
#            MAC0219 - Programacao Concorrente e Paralela - MiniEP2            #
#                                                                              #
#                                   Makefile                                   #
#                                                                              #
#                       Marcelo Schmitt   - NUSP 9297641                       #
#                       Raphael R. Gusmao - NUSP 9778561                       #
################################################################################

.PHONY: clean
CC = g++
CFLAGS = -Wall -O2 -g
OBJS = \
	frog.o \
	lake.o \
	miniep2.o

all: miniep2

miniep2: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lpthread
	make clean

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *~

run:
	./miniep2 3 3

################################################################################
