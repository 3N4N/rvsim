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

  uint32_t instrs[] = {
    0xfe010113,
    0x02010413,
    0xfef42623,
    0x00000793,
    0x02010113,
  };

  for (size_t i = 0; i < sizeof(instrs) / sizeof(instrs[0]); ++i) {
    printf("Decoding %u\n", instrs[i]);
    Instruction instr = decode(instrs[i]);
    instr.print();
  }

  return 0;
}
