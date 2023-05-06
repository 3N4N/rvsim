CXX         = c++
CXXFLAGS    = -g -Wall -std=c++17 -Iinc/
LIBS        =

SRCS   = $(wildcard src/*.cc)
OBJS   = $(patsubst src/%.cc,bin/%.o,$(SRCS))
DEPS   = $(OBJS:.o:=.d)
DIRS   = src inc bin
EXE    = rvsim

all: $(DIRS) $(EXE)

$(DIRS):
	mkdir -p $@

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(LIBS)

bin/%.o : src/%.cc
	$(CXX) -o $@ $(CXXFLAGS) -c $<

bin/%.o : src/%.cc inc/%.h
	$(CXX) -o $@ $(CXXFLAGS) -c $<

clean:
	rm -rf bin *~ $(EXE)

