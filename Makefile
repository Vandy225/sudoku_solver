CCC = g++

CCCFLAGS = -Wall -g -std=c++11 -lpthread -lX11

DEPS = main.o puzzle.o solver.o

all : main

main : $(DEPS)
	$(CCC) $(CCCFLAGS) -o $@ $^

%.o : %.cc
	$(CCC) $(CCCFLAGS) -c $<

clean:
	rm -f *.o *~ *% *# .#* main

clean-all: clean
	rm -f main
