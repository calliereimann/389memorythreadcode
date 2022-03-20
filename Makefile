CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -Werror -std=c++17 -g
OPTFLAGS = -O3
LDFLAGS=$(CXXFLAGS)

all: benchmark barrier_test

benchmark: benchmark.o
	$(CXX) $(LDFLAGS) $(OPTFLAGS) -o $@ $^

barrier_test: barrier_test.o
	$(CXX) $(LDFLAGS) -pthread -o $@ $^

%.o: %.cc %.hh
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -c -o $@ $<

clean:
	rm -rf *.o benchmark barrier_test
