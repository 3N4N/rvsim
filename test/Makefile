CXX         = c++
CXXFLAGS    = -g -Wall -std=c++17 -Iinclude/ -I../include
LIBS        =

TESTS       = $(wildcard tests/*.cc)
OBJS        = $(wildcard ../obj/*.o)
OBJS       := $(filter-out ../obj/main.o, $(OBJS))
DEPS        = $(OBJS:.o:=.d)
EXES        = $(patsubst tests/%.cc,bin/%,$(TESTS))
DIRS        = tests include bin obj

all: $(DIRS) $(EXES)

$(DIRS):
	mkdir -p $@

bin/%: obj/%.o $(OBJS)
	$(CXX) $(LIBS) $^ -o $@

obj/%.o : tests/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf obj bin *~ $(EXES)
