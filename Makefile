cardano: 
	gcc cardano_triplets.c -o cardano $(CONFIG)

parallel:
	gcc cardano_triplets.c -o cardano $(PARCONFIG)

clean:
	rm -f cardano *.o core core.*

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

test: debug
	time ./cardano 100
	
