FLAGS=-pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm -std=c++11
COMPILLER=g++

#all: lib start
all: start

#start: main.o
#	$(COMPILLER) $(FLAGS) -o da-lab4 main.o -L. lib/lib-z-search.a

start: main.o
	$(COMPILLER) $(FLAGS) -o a.out main.o

main.o: main.cpp
	$(COMPILLER) -c $(FLAGS) main.cpp

clear:
	-rm -f *.o *.gch *.dat a.out
