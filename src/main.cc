#include <cstdint>
#include <cstring>
#include <cstdio>

#include "util.h"
#include "instruction.h"
#include "decoder.h"
#include "control.h"
#include "alu.h"
#include "memory.h"
#include "regfile.h"
#include "exec.h"

using namespace std;

uint8_t   ram[RAM_SZ];
uint32_t  ram_start;

reg_t     regfile[N_REGS];

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
  };

  memset(ram, 0, RAM_SZ);
  memset(regfile, 0, N_REGS * sizeof(reg_t));

  // TODO: read from ELF
  uint32_t _start = 0x80000000;
  uint32_t _end   = _start + sizeof(instrs);

  ram_start = _start;

  // Load instructions in ram
  for (size_t i = 0; i < sizeof(instrs)/sizeof(instrs[0]); ++i) {
    write_ram_u32(ram_start + i*4, instrs[i]);
  }

  // TODO: set PC to ram_start?
  uint32_t PC = ram_start;

  for (;;) {
    if (PC == _end) break;
    instr_t instr;
    read_ram_u32(PC, &instr);
    exec_instr(instr, PC);
  }

  return 0;
}
