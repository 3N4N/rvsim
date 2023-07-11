#pragma once

#include <cstdint>

class Control {
public:
  bool    alu_src;
  bool    mem_to_reg;
  bool    reg_write;
  bool    mem_read;
  bool    mem_write;
  bool    branch;
  uint8_t alu_op;

  Control(uint8_t opcode);
};
