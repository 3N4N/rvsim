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

  vector<reg_t> regfile {
    0, 0, 2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 8, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
  };

  vector<instr_t> instrs {
      0x009a0ab3,   // add x21, x20, x9
      0x40aa8b33,   // sub x22, x21, x10
      0x00aafcb3,   // and x25, x21, x10
      0x00d74ab3,   // xor x21, x14, x13
      0x038a0493,   // addi x9, x20, 56
      0x402a54b3,   // sra  x9, x20, x2
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
    uint32_t rd1 = regfile[instr.rs1];
    uint32_t rd2 = regfile[instr.rs2];
    regfile[instr.rd] = alu(rd1, instr.format == I ? instr.imm : rd2,
                            alu_op_map.at((instr.funct7>>2) | instr.funct3));
    for (size_t i = 0; i < 32/8; ++i) {
      for (int j = 0; j < 8; ++j) {
        printf("\t%d", static_cast<int32_t>(regfile[i*8+j]));
      }
      puts("");
    }
  }

  return 0;
}
