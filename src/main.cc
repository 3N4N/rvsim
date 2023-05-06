#include <iostream>
#include <sstream>
#include <chrono>
#include "decoder.h"

using namespace std;

#define TIMER_SETUP \
  std::chrono::time_point<std::chrono::high_resolution_clock> __start, __stop;
#define TIMER_START __start = std::chrono::high_resolution_clock::now();
#define TIMER_STOP  __stop  = std::chrono::high_resolution_clock::now();
#define TIMER_DURATION \
  (std::chrono::duration_cast<std::chrono::microseconds>(__stop-__start).count())

int
main(int argc, char **argv)
{
  puts("Hello world");

  string instrs[] = {
    "fe010113",
    "02010413",
    "fef42623",
    "00000793",
    "02010113",
  };

  for (size_t i = 0; i < sizeof(instrs) / sizeof(instrs[0]); ++i) {
    printf("Decoding %s\n", instrs[i].c_str());
    Instruction instr = decode(instrs[i]);
    instr.print();
  }

  return 0;
}
