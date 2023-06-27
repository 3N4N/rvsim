#include "regfile.h"
#include <cstdio>

void
dump_regs()
{
  for (int i = 0; i < N_REGS / 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      printf("X%02d: %#-12X", i*4+j, regfile[i*4+j]);
    }
    puts("");
  }
  puts("");
}
