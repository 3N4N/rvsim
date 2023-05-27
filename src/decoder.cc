#include <iostream>
#include <unordered_map>
#include "decoder.h"

using namespace std;

#define RDOFFSET  7
#define RS1OFFSET 15
#define RS2OFFSET 20
#define F3OFFSET  12
#define F7OFFSET  25
#define REGMAX  31
#define F3MAX   7   // 2 ^ (14-12+1)  - 1
#define F7MAX   127 // 2 ^ (31-25+1)  - 1

Instruction
decode(const instr_t _instr)
{
  // TODO: verify/test imm calculation

  uint8_t     opcode(0), rd(0), rs1(0), rs2(0), funct3(0), funct7(0);
  uint32_t    imm(0);
  mnemonic_t  mnemonic;
  format_t    format;

  const unordered_map<uint8_t, format_t> format_map = {
    { 0b0110011, R },
    { 0b0010011, I },
    { 0b1100011, B },
    { 0b0000011, I },
    { 0b0100011, S },
  };

  opcode          = _instr & 127;
  format          = format_map.at(opcode);
  switch(format) {
    case R:
      rd          = (_instr >> RDOFFSET)  & REGMAX;
      rs1         = (_instr >> RS1OFFSET) & REGMAX;
      rs2         = (_instr >> RS2OFFSET) & REGMAX;
      funct3      = (_instr >> F3OFFSET) & F3MAX;
      funct7      = (_instr >> F7OFFSET) & F7MAX;
      break;
    case I:
      rd          = (_instr >> RDOFFSET)  & REGMAX;
      rs1         = (_instr >> RS1OFFSET) & REGMAX;
      funct3      = (_instr >> F3OFFSET) & F3MAX;
      imm         = (_instr >> RS2OFFSET) & 4095;
      break;
    case S:
      rs1         = (_instr >> RS1OFFSET) & REGMAX;
      rs2         = (_instr >> RS2OFFSET) & REGMAX;
      funct3      = (_instr >> F3OFFSET) & F3MAX;
      imm         = ((_instr >> RDOFFSET) & REGMAX) |
                    (((_instr >> F7OFFSET) & F7MAX) << 5);
      break;
    case B:
      rs1         = (_instr >> RS1OFFSET) & REGMAX;
      rs2         = (_instr >> RS2OFFSET) & REGMAX;
      funct3      = (_instr >> F3OFFSET) & F3MAX;
      imm         = (((_instr >> 31) & 0x1) << 12) |
                    (((_instr >> 25) & 0x3f) << 5) |
                    (((_instr >> 7) & 0x1) << 11) |
                    (((_instr >> 8) & 0xf) << 1);
      break;
    case U:
      rd          = (_instr >> RDOFFSET)  & REGMAX;
      imm         = (_instr >> F3OFFSET) << 12;
      break;
    case J:
      rd          = (_instr >> RDOFFSET)  & REGMAX;
      imm         = (((_instr >> 12) & 0xff) << 12) |
                    (((_instr >> 20) & 0x1) << 11) |
                    (((_instr >> 21) & 0x3ff) << 1) |
                    (((_instr >> 31) & 0x1) << 20);
      break;
    default:
      puts("[ERR] This should not be possible to reach!");
      break;
  }

  const unordered_map<uint32_t, mnemonic_t> mnemonic_map {
    // { (f7<<10 | f3<<7 | opcode), mnemonic }
    // Opcode         f3         f7
    { (0b0110011 | (0x0<<7) | (0x00<<10)),  ADD },
    { (0b0110011 | (0x0<<7) | (0x20<<10)),  SUB },
    { (0b0110011 | (0x4<<7) | (0x00<<10)),  XOR },
    { (0b0110011 | (0x6<<7) | (0x00<<10)),  OR },
    { (0b0110011 | (0x7<<7) | (0x00<<10)),  AND },
    { (0b0110011 | (0x1<<7) | (0x00<<10)),  SLL },
    { (0b0110011 | (0x5<<7) | (0x00<<10)),  SRL },
    { (0b0110011 | (0x5<<7) | (0x20<<10)),  SRA },
    { (0b0010011 | (0x0<<7)),               ADDI },
    { (0b0010011 | (0x4<<7)),               XORI },
    { (0b0010011 | (0x6<<7)),               ORI },
    { (0b0010011 | (0x7<<7)),               ANDI },
    { (0b0010011 | (0x1<<7) | (0x00<<10)),  SLLI },
    { (0b0010011 | (0x5<<7) | (0x00<<10)),  SRLI },
    { (0b0010011 | (0x5<<7) | (0x20<<10)),  SRAI },
    { (0b0000011 | (0x2<<7)),               LW },
    { (0b0100011 | (0x2<<7)),               SW },
    { (0b1100011 | (0x0<<7)),               BEQ },
  };

  mnemonic = mnemonic_map.at(opcode | (funct3<<7) | (funct7<<10));

  Instruction instr(opcode, rd, rs1, rs2, funct3, funct7, imm, mnemonic, format);
  return instr;
}
