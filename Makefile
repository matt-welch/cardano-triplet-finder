#/*******************************************************************************
# * FILENAME:    Makefile
# * DESCRIPTION: build options for cardano_triplets.c 
# * AUTHOR:      James Matthew Welch [JMW]
# * SCHOOL:      Arizona State University
# * CLASS:       CSE598: High Performance Computing
# * INSTRUCTOR:  Dr. Gil Speyer
# * SECTION:     20520
# * TERM:        Spring 2013
# *******************************************************************************/
#
all: cardano parallel

cardano: 
	gcc cardano_triplets.c -o cardano $(CONFIG)

parallel:
	gcc cardano_triplets.c -o cardano_parallel $(PARCONFIG)

clean:
	rm -f cardano cardano_parallel cardano_is cardano_ip *.o core core.*

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

option1: CONFIG= -O0 -lm -DQUIET
option1: cardano

option2: CONFIG= -O3 -lm -DQUIET
option2: cardano


quiet: CONFIG=$(EASY_FLAGS) -DQUIET
quiet: all

test: quiet 
	time ./cardano 1000
	time ./cardano_parallel 1000
	
