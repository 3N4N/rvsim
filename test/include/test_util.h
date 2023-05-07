#ifndef _TEST_UTIL_H_
#define _TEST_UTIL_H_


#include <chrono>

#define TIMER_SETUP \
  std::chrono::time_point<std::chrono::high_resolution_clock> __start, __stop;
#define TIMER_START __start = std::chrono::high_resolution_clock::now();
#define TIMER_STOP  __stop  = std::chrono::high_resolution_clock::now();
#define TIMER_DURATION \
  (std::chrono::duration_cast<std::chrono::microseconds>(__stop-__start).count())


#define ASSERT( cond, fmt, ... )                               \
{                                                                   \
  if (!(cond) ) {                                            \
    printf("[FAIL] %s: ", __FILE__);    \
    printf(fmt, __VA_ARGS__);     \
  }                                                                 \
}

#endif  // _TEST_UTIL_H_
