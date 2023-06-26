#include <iostream>
#include "decoder.h"
#include "test_util.h"

using namespace std;

int
main(int argc, char **argv)
{
  puts("Testing decoder...");

  uint32_t instrbits = 0xfe010113;

  Instruction instr = decode(instrbits);
  // instr.print();
  TEST((instr.opcode==0b0010011),
      "Decode 0x%x\n", instrbits);

  return 0;
}
