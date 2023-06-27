#ifndef _REGFILE_H_
#define _REGFILE_H_

#include "util.h"

#define N_REGS      32

extern reg_t regfile[N_REGS];

void dump_regs();

#endif  // _REGFILE_H_
