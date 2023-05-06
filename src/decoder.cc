#include "decoder.h"
#include <sstream>
#include <unordered_map>

using namespace std;

#define RDOFFSET  7
#define RS1OFFSET 15
#define RS2OFFSET 20
#define F3OFFSET  12
#define F7OFFSET  25
#define REGMAX  31
#define F3MAX   7   // 2 ^ (14-12+1)  - 1
#define F7MAX   127 // 2 ^ (31-25+1)  - 1

void
Instruction::print()
{
  puts("format\tmnemonic\topcode\trd\trs1\trs2\tfunct3\timm");
  printf("%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n",
      _format_map[format].c_str(),
      _mnemonic_map[mnemonic].c_str(),
      opcode, rd, rs1, rs2, funct3, imm);
}

unordered_map<uint8_t, format_t> format_map {
  { 0b0110011, R },
  { 0b0010011, I },
  { 0b1100011, B },
  { 0b0000011, I },
  { 0b0100011, S },
};

unordered_map<uint32_t, mnemonic_t> mnemonic_map {
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
  { (0b0010011 | (0x0<<7)),  ADDI },
  { (0b0010011 | (0x4<<7)),  XORI },
  { (0b0010011 | (0x6<<7)),  ORI },
  { (0b0010011 | (0x7<<7)),  ANDI },
  { (0b0010011 | (0x1<<7) | (0x00<<10)),  SLLI },
  { (0b0010011 | (0x5<<7) | (0x00<<10)),  SRLI },
  { (0b0010011 | (0x5<<7) | (0x20<<10)),  SRAI },
  { (0b0000011 | (0x2<<7)),  LW },
  { (0b0100011 | (0x2<<7)),  SW },
  { (0b1100011 | (0x0<<7)),  BEQ },
};

Instruction
decode(const string& __instr)
{
  // TODO: test instr is hexstring

  stringstream ss;
  ss << hex << __instr;
  uint32_t _instr;
  ss >> _instr;

  Instruction instr;
  instr.opcode      = _instr & 127;
  instr.format      = format_map[instr.opcode];

  switch(instr.format) {
    case R:
      instr.rd          = (_instr >> RDOFFSET)  & REGMAX;
      instr.rs1         = (_instr >> RS1OFFSET) & REGMAX;
      instr.rs2         = (_instr >> RS2OFFSET) & REGMAX;
      instr.funct3      = (_instr >> F3OFFSET) & F3MAX;
      instr.funct7      = (_instr >> F7OFFSET) & F7MAX;
      break;
    case I:
      instr.rd          = (_instr >> RDOFFSET)  & REGMAX;
      instr.rs1         = (_instr >> RS1OFFSET) & REGMAX;
      instr.funct3      = (_instr >> F3OFFSET) & F3MAX;
      instr.imm         = (_instr >> RS2OFFSET) & 4095;
      break;
    case S:
      instr.rs1         = (_instr >> RS1OFFSET) & REGMAX;
      instr.rs2         = (_instr >> RS2OFFSET) & REGMAX;
      instr.funct3      = (_instr >> F3OFFSET) & F3MAX;
      instr.imm         = ((_instr >> RDOFFSET) & REGMAX) |
                          (((_instr >> F7OFFSET) & F7MAX) << 5);
      break;
    case B:
      instr.rs1         = (_instr >> RS1OFFSET) & REGMAX;
      instr.rs2         = (_instr >> RS2OFFSET) & REGMAX;
      instr.funct3      = (_instr >> F3OFFSET) & F3MAX;
      // TODO: check imm calculation
      instr.imm         = ((_instr >> (31 - 12)) & (1 << 12)) |
                          ((_instr >> (25 - 5)) & 0x7e0) |
                          ((_instr >> (8 - 1)) & 0x1e) |
                          ((_instr << (11 - 7)) & (1 << 11));
      instr.imm = (instr.imm << 19) >> 19;

      break;
    case U:
      instr.rd          = (_instr >> RDOFFSET)  & REGMAX;
      instr.imm         = (_instr >> F3OFFSET) << 12;
      break;
    case J:
      instr.rd          = (_instr >> RDOFFSET)  & REGMAX;
      // TODO: calculate imm
      break;
    default:
      puts("[ERR] This should not be possible to reach!");
      break;
  }

  instr.mnemonic    = mnemonic_map[
    instr.opcode | (instr.funct3<<7) | (instr.funct7<<10)
  ];

  // instr.print();

  return instr;
}
