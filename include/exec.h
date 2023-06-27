#ifndef _EXEC_H_
#define _EXEC_H_

#include "util.h"
#include "instruction.h"

void exec_instr(instr_t _instr, uint32_t &PC);

#endif  // _EXEC_H_
