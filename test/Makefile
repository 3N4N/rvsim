CXX         = c++
CXXFLAGS    = -g -Wall -std=c++17 -Iinclude/ -I../include
LIBS        =

TESTS       = $(wildcard tests/*.cc)
OBJS        = $(wildcard ../objs/*.o)
OBJS       := $(filter-out ../objs/main.o, $(OBJS))
DEPS        = $(OBJS:.o:=.d)
EXES        = $(patsubst tests/%.cc,bin/%,$(TESTS))
DIRS        = tests include bin objs

all: $(DIRS) $(EXES)

$(DIRS):
	mkdir -p $@

bin/test_decode: objs/test_decode.o $(OBJS)
	$(CXX) $(LIBS) $^ -o $@

bin/test_alu: objs/test_alu.o $(OBJS)
	$(CXX) $(LIBS) $^ -o $@

objs/%.o : tests/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf objs bin *~ $(EXES)
