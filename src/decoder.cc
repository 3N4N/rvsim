#include "decoder.h"
#include <sstream>

using namespace std;

void
Instruction::print()
{
  puts("format\topcode\trd\trs1\trs2\tfunct3\tfunct7\timm");
  printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
      format_map[format].c_str(), opcode, rd, rs1, rs2, funct3, funct7, imm);
}

Instruction
decode(const string& __instr)
{
  // TODO: test instr is hexstring

  stringstream ss;
  ss << hex << __instr;
  uint32_t _instr;
  ss >> _instr;

  Instruction instr;
  instr.opcode  = _instr & 127;
  instr.rd      = (_instr >> 7)  & 31;
  instr.rs1     = (_instr >> 15) & 31;
  instr.rs2     = (_instr >> 20) & 31;
  instr.funct3  = (_instr >> 12) & 7;

  // instr.print();

  // https://inst.eecs.berkeley.edu/~cs250/fa11/handouts/riscv-spec.pdf
  switch(instr.opcode) {
    case 0b0110011:
      instr.format = R;
      // add sub xor or and sll srl sra slt sltu
      break;
    case 0b0010011:
      // addi xori ori andi slli srli srai slti sltiu
      instr.format = I;
      break;
    case 0b1100011:
      // beq bne blt bge bltu bgeu
      instr.format = B;
      break;
    case 0b0000011:
      // lb lh lw lbu lhu
      instr.format = I;
      break;
    case 0b0100011:
      // sb sh sw
      instr.format = S;
      break;
  }

  return instr;
}
