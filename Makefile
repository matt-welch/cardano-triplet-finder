cardano: 
	gcc cardano_triplets.c -o cardano $(CONFIG)

clean:
	rm -f cardano *.o core core.*

tidy: clean
	rm -f *.*~ *~

DEBUG_FLAGS = -g3 -ggdb -O0 -Wall -pedantic -DDEBUG -lpthread -lm
CONFIG		= -Wall -pedantic -lpthread -O3 -lm
EASY_FLAGS	= -lpthread -lm

debug: CONFIG=$(DEBUG_FLAGS)
debug: cadrano

easy: CONFIG=$(EASY_FLAGS)
easy: cardano

test: debug
	./cardano
	
