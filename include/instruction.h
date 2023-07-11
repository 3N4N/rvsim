#pragma once

#include <cstdint>

using instr_t = uint32_t;

typedef enum {
  ADD, SUB, ADDI, AND, OR, XOR, ANDI, ORI, XORI, BEQ, LW, SW, SLL, SLLI, SRL,
  SRLI, SRA, SRAI,
} mnemonic_t;

typedef enum {
  R, I, S, B, U, J,
} format_t;

class Instruction {
public:
  const uint8_t     opcode;
  const uint8_t     rd;
  const uint8_t     rs1;
  const uint8_t     rs2;
  const uint8_t     funct3;
  const uint8_t     funct7;
  const uint32_t    imm;
  const mnemonic_t  mnemonic;
  const format_t    format;

  Instruction(
      uint8_t _opcode, uint8_t _rd, uint8_t _rs1, uint8_t _rs2,
      uint8_t _funct3, uint8_t _funct7, uint32_t _imm,
      mnemonic_t _mnemonic, format_t _format) :
    opcode(_opcode), rd(_rd), rs1(_rs1), rs2(_rs2),
    funct3(_funct3), funct7(_funct7), imm(_imm),
    mnemonic(_mnemonic), format(_format)
    {}
  void print();
};
