CXX         = c++
CXXFLAGS    = -g -Wall -std=c++17 -Iinclude/
LIBS        =

SRCS   = $(wildcard src/*.cc)
OBJS   = $(patsubst src/%.cc,objs/%.o,$(SRCS))
DEPS   = $(OBJS:.o:=.d)
DIRS   = src include objs
EXE    = rvsim

all: $(DIRS) $(EXE)

$(DIRS):
	mkdir -p $@

$(EXE): $(OBJS)
	$(CXX) $(LIBS) $^ -o $@

objs/%.o : src/%.cc include/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

objs/%.o : src/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf objs *~ $(EXE)
