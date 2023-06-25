#ifndef _REGFILE_H_
#define _REGFILE_H_

reg_t regfile[32] = {
  0, 0, 2, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 8, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
};

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

#endif  // _REGFILE_H_
