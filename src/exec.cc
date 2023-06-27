#include <cstdio>
#include "exec.h"
#include "decoder.h"
#include "control.h"
#include "alu.h"
#include "memory.h"
#include "regfile.h"

void
exec_instr(instr_t _instr, uint32_t &PC)
{
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
    uint32_t addr = alu_out;
    if (write_ram(addr, rd2, instr.funct3)) {
      puts("[ERR] write_ram failed");
    }
  }


  // -- WB stage ---------------------------------------------------------------

  if (ctrl.reg_write) {
    regfile[instr.rd] = ctrl.mem_to_reg ? ram_data : alu_out;
  }

  PC += 4;
  dump_regs();
}
