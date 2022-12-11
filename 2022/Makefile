.SUFFIXES:

sources := $(wildcard *.cpp)
objects := ${sources:.cpp=}

benchs_src := $(wildcard *bench.cc)
benchs := ${benchs_src:.cc=}

all: $(objects)

bench: $(benchs)

$(objects): %: %.cpp
	$(CXX) -o $@ $< -std=c++17 -Wall -I.. -O3 -march=native -lstdc++

$(benchs): %: %.cc
	$(CXX) -o $@ $< -std=c++17 -Wall -I.. -O3 -march=native -lbenchmark -lpthread -lstdc++

clean:
	@rm $(objects) &> /dev/null || true
	@rm $(benchs) &> /dev/null || true

run_all:
	./run.sh

bench_all:
	./bench.sh

.PHONY:
	all

