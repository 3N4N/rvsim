#include <iostream>
#include <sstream>
#include "decoder.h"

using namespace std;

int
main(int argc, char **argv)
{
  puts("Hello world");
  Instruction instr = decode("fe010113");
  instr.print();

  return 0;
}
