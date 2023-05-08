#include "alu.h"
#include <cstdint>
#include <iostream>

uint32_t
alu(reg_t rd1, reg_t rd2, alu_op_t aluop)
{
  uint32_t result(0);

  switch (aluop) {
    case ALU_ADD:
      result = rd1 + rd2; break;
    case ALU_SUB:
      result = rd1 - rd2; break;
    case ALU_XOR:
      result = rd1 ^ rd2; break;
    case ALU_OR:
      result = rd1 | rd2; break;
    case ALU_AND:
      result = rd1 & rd2; break;
    case ALU_SLT:
      result = rd1 < rd2; break;
    default:
      puts("[ERR] alu: this should not be possible to reach!");
  }

  return result;
}
