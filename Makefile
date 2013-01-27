all: cardano parallel

cardano: 
	gcc cardano_triplets.c -o cardano $(CONFIG)

parallel:
	gcc cardano_triplets.c -o cardano_parallel $(PARCONFIG)

clean:
	rm -f cardano cardano_parallel *.o core core.*

tidy: clean
	rm -f *.*~ *~

DEBUG_FLAGS = -g3 -ggdb -O0 -Wall -pedantic -DDEBUG -fopenmp -lm
CONFIG		= -Wall -pedantic -fopenmp -O3 -lm
PARCONFIG	= $(CONFIG) -DPARALLEL
EASY_FLAGS	= -fopenmp -lm

debug: CONFIG=$(DEBUG_FLAGS)
debug: cardano

easy: CONFIG=$(EASY_FLAGS)
easy: cardano

quiet: CONFIG=$(EASY_FLAGS) -DQUIET
quiet: all

test: quiet 
	time ./cardano 1000
	time ./cardano_parallel 1000
	
