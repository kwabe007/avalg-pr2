CFLAGS=-g -Wall -std=c++11
GMP_LINK=-lgmpxx -lgmp
clean:
	-rm bin

bin:	clean main.cpp
	g++ $(CFLAGS) -o bin main.cpp $(GMP_LINK)

clean_test:
	-rm test

test: clean_test test.cpp
	g++ $(CFLAGS) -o test test.cpp $(GMP_LINK)
