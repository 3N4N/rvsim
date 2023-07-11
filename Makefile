CXX         = c++
CXXFLAGS    = -g -Wall -std=c++17 -Iinclude/ -MP -MMD
LIBS        =

SRCS   = $(wildcard src/*.cc)
OBJS   = $(patsubst src/%.cc,obj/%.o,$(SRCS))
DEPS   = $(OBJS:.o=.d)
DIRS   = src include obj
EXE    = rvsim

all: $(DIRS) $(EXE)

$(DIRS):
	mkdir -p $@

$(EXE): $(OBJS) $(DIRS)
	$(CXX) $(LIBS) $(OBJS) -o $@

obj/%.o : src/%.cc include/%.h $(DIRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/%.o : src/%.cc $(DIRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf obj *~ $(EXE)

-include $(DEPS)
