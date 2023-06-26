#ifndef _TEST_UTIL_H_
#define _TEST_UTIL_H_


#include <chrono>
#include "util.h"
#include "control.h"
#include "alu.h"
#include "memory.h"
#include "regfile.h"

#define TIMER_SETUP \
  std::chrono::time_point<std::chrono::high_resolution_clock> __start, __stop;
#define TIMER_START __start = std::chrono::high_resolution_clock::now();
#define TIMER_STOP  __stop  = std::chrono::high_resolution_clock::now();
#define TIMER_DURATION \
  (std::chrono::duration_cast<std::chrono::microseconds>(__stop-__start).count())


#define ASSERT( cond, fmt, ... )        \
{                                       \
  if (!(cond) ) {                       \
    printf("[FAIL] %s: ", __FILE__);    \
    printf(fmt, __VA_ARGS__);           \
  }                                     \
}

#define TEST( cond, fmt, ... )          \
{                                       \
  if (!(cond) ) {                       \
    printf("[FAIL] %s: ", __FILE__);    \
  } else {                              \
    printf("[PASS] %s: ", __FILE__);    \
  }                                     \
  printf(fmt, __VA_ARGS__);           \
}

int
eq_regfile(reg_t *_regfile)
{
  for (int i = 0; i < N_REGS; ++i) {
    if (_regfile[i] != regfile[i])
      return 0;
  }
  return 1;
}

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

#endif  // _TEST_UTIL_H_
