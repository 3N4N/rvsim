#include <cstdio>
#include <cstring>
#include "util.h"
#include "instruction.h"
#include "decoder.h"
#include "control.h"
#include "alu.h"
#include "memory.h"
#include "regfile.h"
#include "exec.h"
#include "test_util.h"

using namespace std;

uint8_t   ram[RAM_SZ];
uint32_t  ram_start;
reg_t     regfile[N_REGS];

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

    for (size_t i = 0; i < sizeof(instrs)/sizeof(instrs[0]); ++i) {
      uint32_t _PC = 0x0;
      exec_instr(instrs[i], _PC);
    }

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
      0x10732023,   // sw   x7, 256(x6)
    };

    memset(ram, 0, RAM_SZ);
    memset(regfile, 0, N_REGS * sizeof(reg_t));
    regfile[7] = 0x20;

    for (size_t i = 0; i < sizeof(instrs)/sizeof(instrs[0]); ++i) {
      uint32_t _PC = 0x0;
      exec_instr(instrs[i], _PC);
    }

    TEST((ram[0x80000100-ram_start] == 0x20), "%s\n", "SW");
  }

  return 0;
}
