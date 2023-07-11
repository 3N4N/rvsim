#pragma once

#include "util.h"

#define N_REGS      32

extern reg_t regfile[N_REGS];

void dump_regs();
