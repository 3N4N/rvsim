#include <cstdint>
#include <iostream>

#include "util.h"
#include "instruction.h"
#include "decoder.h"
#include "control.h"
#include "alu.h"
#include "memory.h"
#include "regfile.h"

using namespace std;

int
main(int argc, char **argv)
{
  puts("This is RISC-V");

  instr_t instrs[] = {
    0x009a0ab3,   // add  x21,  x20,  x9
    0x40aa8b33,   // sub  x22,  x21,  x10
    0x00aafcb3,   // and  x25,  x21,  x10
    0x00d74ab3,   // xor  x21,  x14,  x13
    0x038a0493,   // addi x9,   x20,  56
    0x402a54b3,   // sra  x9,   x20,  x2
    // 0x3e802303,   // lw   x6 ,  0x1000(x0)
    0x00100313,
    0x01f31313,
    0x00832383    // lw  x7,8(x6)
  };

  // In reality, it is read from ELF (_start symbol)
  ram_start = 0x80000000;

  // TODO: Load instructions in ram

  // TODO: set PC to ram_start?

  for (auto _instr: instrs) {
    uint32_t        rd1, rd2;
    uint8_t         alu_ctrl;
    uint32_t        alu_out;
    uint32_t        ram_data;

    // -- ID Stage ---------------------------------------------------------------

    Instruction instr = decode(_instr);
    instr.print();

    Control ctrl(instr.opcode);
    rd1 = regfile[instr.rs1];
    rd2 = regfile[instr.rs2];


    // -- EX stage ---------------------------------------------------------------

    alu_ctrl  = get_alu_ctrl(ctrl.alu_op, instr.funct3, instr.funct7);
    alu_out   = alu(rd1, ctrl.alu_src ? instr.imm : rd2, alu_ctrl);


    // -- MEM stage --------------------------------------------------------------

    if (ctrl.mem_read) {
      uint32_t addr = alu_out;
      if (read_ram(addr, &ram_data, instr.funct3)) {
        puts("[ERR] main: read_ram failed");
      }
    } else {
      ram_data = 0;
    }

    if (ctrl.mem_write) {
      // TODO: write rd2 to ram at alu_out
    }


    // -- WB stage ---------------------------------------------------------------

    if (ctrl.reg_write) {
      regfile[instr.rd] = ctrl.mem_to_reg ? ram_data : alu_out;
    }

    dump_regs();
  }

  return 0;
}
