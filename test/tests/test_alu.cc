#include <iostream>
#include <unordered_map>
#include <vector>
#include "util.h"
#include "instruction.h"
#include "decoder.h"
#include "alu.h"

using namespace std;

int
main(int argc, char **argv)
{
  puts("This is RISC-V");

  size_t n_regs = 32;
  vector<reg_t> regfile;
  regfile.resize(n_regs);

  vector<instr_t> instrs {
      0x009a0ab3,   // add x21, x20, x9
      0x40aa8b33,   // sub x22, x21, x10
      0x00aafcb3,   // and x25, x21, x10
      0x00d74ab3,   // xor x21, x14, x13
  };

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

  for (auto _instr: instrs) {
    Instruction instr = decode(_instr);
    instr.print();
    reg_t rd1 = regfile[instr.rs1];
    reg_t rd2 = regfile[instr.rs2];
    alu(rd1, rd2, alu_op_map.at((instr.funct7>>2) | instr.funct3));
  }

  return 0;
}
