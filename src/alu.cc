#include "alu.h"
#include <cstdint>
#include <iostream>
#include <unordered_map>

uint32_t
alu(uint32_t rd1, uint32_t rd2, uint8_t aluop)
{
  uint32_t result(0);

  typedef enum {
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
  } alu_op_t;

  const static std::unordered_map<uint8_t, alu_op_t> alu_op_map {
    { 0b0000, ALU_ADD },
    { 0b1000, ALU_SUB },
    { 0b0100, ALU_XOR },
    { 0b0110, ALU_OR },
    { 0b0111, ALU_AND },
    { 0b0001, ALU_SLL },
    { 0b0101, ALU_SRL },
    { 0b1101, ALU_SRA },
    { 0b0010, ALU_SLT },
    { 0b0011, ALU_SLTU },
  };

  switch (alu_op_map.at(aluop)) {
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
