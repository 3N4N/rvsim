#include "instruction.h"

#include <iostream>
#include <unordered_map>

const std::unordered_map<format_t, std::string> _format_t_map {
  {R, "R"}, {I, "I"}, {S, "S"}, {B, "B"}, {U, "U"}, {J, "J"},
};

const std::unordered_map<mnemonic_t, std::string> _mnemonic_t_map {
  { ADD,  "ADD" },
    { SUB,  "SUB" },
    { ADDI, "ADDI" },
    { AND,  "AND" },
    { OR,   "OR" },
    { XOR,  "XOR" },
    { ANDI, "ANDI" },
    { ORI,  "ORI" },
    { XORI, "XORI" },
    { BEQ,  "BEQ" },
    { LW,   "LW" },
    { SW,   "SW" },
    { SLL,  "SLL" },
    { SLLI, "SLLI" },
    { SRL,  "SRL" },
    { SRLI, "SRLI" },
    { SRA,  "SRA" },
    { SRAI, "SRAI" },
};

void
Instruction::print()
{
  puts("format\tmnemonic\topcode\trd\trs1\trs2\tfunct3\timm");
  printf("%s\t%s\t\t%d\t%d\t%d\t%d\t%d\t0x%x\n",
      _format_t_map.at(format).c_str(),
      _mnemonic_t_map.at(mnemonic).c_str(),
      opcode, rd, rs1, rs2, funct3, imm);
}
