#ifndef _ALU_H_
#define _ALU_H_

#include "util.h"

enum alu_op_t {
  ALU_ADD,
  ALU_SUB,
  ALU_XOR,
  ALU_OR,
  ALU_AND,
  ALU_SLL,
  ALU_SRL,
  ALU_SRA,
  ALU_SLT,
  ALU_SLTU,
};


uint32_t alu(reg_t rd1, reg_t rd2, alu_op_t aluop);

#endif  // _ALU_H_
