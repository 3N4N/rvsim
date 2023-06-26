#include <iostream>
#include <cstring>
#include "util.h"
#include "instruction.h"
#include "decoder.h"
#include "control.h"
#include "alu.h"
#include "memory.h"
#include "regfile.h"
#include "test_util.h"

using namespace std;

void
simulate(instr_t instrs[], int n)
{
  for (int i = 0; i < n; ++i) {
    uint32_t        rd1, rd2;
    uint8_t         alu_ctrl;
    uint32_t        alu_out;
    uint32_t        ram_data;

    // -- ID Stage ---------------------------------------------------------------

    Instruction instr = decode(instrs[i]);
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
        puts("[ERR] read_ram failed");
      }
    } else {
      ram_data = 0;
    }

    if (ctrl.mem_write) {
      uint32_t addr = alu_out;
      if (write_ram(addr, rd2, instr.funct3)) {
        puts("[ERR] write_ram failed");
      }
    }


    // -- WB stage ---------------------------------------------------------------

    if (ctrl.reg_write) {
      regfile[instr.rd] = ctrl.mem_to_reg ? ram_data : alu_out;
    }

    dump_regs();
  }
}

int
main(int argc, char **argv)
{
  puts("This is RISC-V");

  ram_start = 0x80000000;

  // Test LW
  {
    instr_t instrs[] = {
      0x00100313,   // addi x6, x0, 1
      0x01f31313,   // slli x6, x6, 31
      0x00832383,   // lw   x7, 8(x6)
    };

    memset(ram, 0, RAM_SZ);
    memset(regfile, 0, N_REGS * sizeof(reg_t));
    ram[8] = 0x10;
    simulate(instrs, sizeof(instrs)/sizeof(instrs[0]));

    reg_t test_regfile[] = {
      0, 0, 0, 0, 0, 0, 0x80000000, 0x10,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
    };

    TEST(eq_regfile(test_regfile), "%s\n", "LW");
  }

  // Test SW
  {
    instr_t instrs[] = {
      0x00100313,   // addi x6, x0, 1
      0x01f31313,   // slli x6, x6, 31
      0x00732423,   // sw   x7, 8(x6)
    };

    memset(ram, 0, RAM_SZ);
    memset(regfile, 0, N_REGS * sizeof(reg_t));
    regfile[7] = 0x20;
    simulate(instrs, sizeof(instrs)/sizeof(instrs[0]));

    TEST((ram[0x80000008-ram_start] == 0x20), "%s\n", "SW");
  }

  return 0;
}
