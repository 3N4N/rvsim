CXX         = c++
CXXFLAGS    = -g -Wall -std=c++17 -Iinclude/
LIBS        =

SRCS   = $(wildcard src/*.cc)
OBJS   = $(patsubst src/%.cc,bin/%.o,$(SRCS))
DEPS   = $(OBJS:.o:=.d)
DIRS   = src include bin
EXE    = rvsim

all: $(DIRS) $(EXE)

$(DIRS):
	mkdir -p $@

$(EXE): $(OBJS)
	$(CXX) $(LIBS) $^ -o $@

bin/%.o : src/%.cc include/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin/%.o : src/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf bin *~ $(EXE)

