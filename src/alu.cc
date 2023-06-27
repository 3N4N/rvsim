#include "alu.h"

#include <cstdint>
#include <cstdio>
#include <unordered_map>


typedef enum {
  ALU_ADD  = 0b0000,
  ALU_SUB  = 0b1000,
  ALU_XOR  = 0b0100,
  ALU_OR   = 0b0110,
  ALU_AND  = 0b0111,
  ALU_SLL  = 0b0001,
  ALU_SRL  = 0b0101,
  ALU_SRA  = 0b1101,
  ALU_SLT  = 0b0010,
  ALU_SLTU = 0b0011,
} alu_op_t;

/// ALU Control
///
///
/// ALU control is a 4-bit signal that tells ALU which operation to perform.
/// Params:
///   * alu_op: 2-bit ALUOp from Control unit
///   * funct3:
///   * funct7: instr[30|14:12]
/// Returns: 4-bit ALU control signal
uint8_t
get_alu_ctrl(uint8_t alu_op, uint8_t funct3, uint8_t funct7)
{
  // 0b1111 is absent from alu_op_t
  // Good choice for initializing alu_ctrl with
  uint8_t alu_ctrl(0b1111);
  switch (alu_op) {
    case 0b00: alu_ctrl = ALU_ADD; break;
    case 0b01: alu_ctrl = ALU_SUB; break;
    case 0b10: alu_ctrl = (funct7>>2) | funct3; break;
    default: puts("[ERR] get_alu_ctrl: this should not be possible to reach!");
  }

  // TODO: assert alu_ctrl != 0b1111

  return alu_ctrl;
}

/// ALU
///
/// Performs the arithmetic logic operation.
/// Params:
///   * rd1:      reg data 1
///   * rd2:      reg data 2
///   * alu_ctrl: 4-bit ALU control that decides which operation to perform
/// Returns:      The result of the operation performed on 'rd1' and 'rd2'
uint32_t
alu(uint32_t rd1, uint32_t rd2, uint8_t alu_ctrl)
{
  uint32_t result(0);

  switch (alu_ctrl) {
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
