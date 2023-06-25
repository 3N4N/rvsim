#ifndef _TEST_UTIL_H_
#define _TEST_UTIL_H_


#include <chrono>
#include "util.h"

#define TIMER_SETUP \
  std::chrono::time_point<std::chrono::high_resolution_clock> __start, __stop;
#define TIMER_START __start = std::chrono::high_resolution_clock::now();
#define TIMER_STOP  __stop  = std::chrono::high_resolution_clock::now();
#define TIMER_DURATION \
  (std::chrono::duration_cast<std::chrono::microseconds>(__stop-__start).count())


#define ASSERT( cond, fmt, ... )        \
{                                       \
  if (!(cond) ) {                       \
    printf("[FAIL] %s: ", __FILE__);    \
    printf(fmt, __VA_ARGS__);           \
  }                                     \
}

#define TEST( cond, fmt, ... )          \
{                                       \
  if (!(cond) ) {                       \
    printf("[FAIL] %s: ", __FILE__);    \
  } else {                              \
    printf("[PASS] %s: ", __FILE__);    \
  }                                     \
  printf(fmt, __VA_ARGS__);           \
}

int
eq_regfile(reg_t *_regfile)
{
  for (int i = 0; i < N_REGS; ++i) {
    if (_regfile[i] != regfile[i])
      return 0;
  }
  return 1;
}

#endif  // _TEST_UTIL_H_
