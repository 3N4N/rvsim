#include <cstdint>
#include <iostream>

#include "util.h"
#include "instruction.h"
#include "decoder.h"
#include "control.h"
#include "alu.h"

using namespace std;

#define N_REGS      32
#define RAM_SZ      0x10000

uint8_t ram[RAM_SZ];
reg_t regfile[32] = {
  0, 0, 2, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 8, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
};


void
dump_regs()
{
  for (int i = 0; i < N_REGS / 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      printf("X%02d: %#-12X", i*4+j, static_cast<int8_t>(regfile[i*4+j]));
    }
    puts("");
  }
  puts("");
}

int
main(int argc, char **argv)
{
  puts("This is RISC-V");

  instr_t instrs[] = {
    0x009a0ab3,   // add x21, x20, x9
    0x40aa8b33,   // sub x22, x21, x10
    0x00aafcb3,   // and x25, x21, x10
    0x00d74ab3,   // xor x21, x14, x13
    0x038a0493,   // addi x9, x20, 56
    0x402a54b3,   // sra  x9, x20, x2
  };

  dump_regs();
  for (auto _instr: instrs) {
    // ID Stage
    Instruction instr = decode(_instr);
    instr.print();

    Control ctrl(instr.opcode);
    uint32_t rd1 = regfile[instr.rs1];
    uint32_t rd2 = regfile[instr.rs2];

    // EX stage
    uint8_t   alu_ctrl  = get_alu_ctrl(ctrl.alu_op, instr.funct3, instr.funct7);
    uint32_t  result    = alu(rd1, instr.format == I ? instr.imm : rd2, alu_ctrl);

    // TODO: MEM stage

    // WB stage
    regfile[instr.rd] = result;
    dump_regs();
  }

  return 0;
}
