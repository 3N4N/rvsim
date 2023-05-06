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
  Instruction instr = decode("fe010113");
  instr.print();

  return 0;
}
