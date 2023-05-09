#include "alu.h"
#include <cstdint>
#include <iostream>

uint32_t
alu(uint32_t rd1, uint32_t rd2, alu_op_t aluop)
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
    case ALU_SLL:
      result = rd1 << rd2; break;
    case ALU_SRL:
      result = rd1 >> rd2; break;
    case ALU_SRA:
      result = static_cast<int32_t>(rd1) >> static_cast<int32_t>(rd2);
      break;
    case ALU_SLT:
      result = static_cast<int32_t>(rd1) < static_cast<int32_t>(rd2);
      break;
    case ALU_SLTU:
      result = rd1 < rd2; break;
    default:
      puts("[ERR] alu: this should not be possible to reach!");
  }

  return result;
}
