CPPFLAGS = -g -O3 -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format
FUNCTIONS_O = solve.o array.o
HEADERS = solve.h data.h array.h
MATH = -lm
VALUEM = -DM=100

%.o: %.cpp $(HEADERS)
	g++ -c $(VALUEM) $(CPPFLAGS) $<
%.out: %.o $(FUNCTIONS_O)
	g++ $(VALUEM) $(CPPFLAGS) $^ -o $@ $(MATH) 
all: a01.out a02.out a03.out a04.out a05.out a06.out a07.out a08.out a09.out a10.out 

archive:
	zip Vatchenko_MY.zip Makefile *.cpp *.h 

rmarchive:
	rm Vatchenko_MY.zip

clean:
	rm -f *.o *.out all
