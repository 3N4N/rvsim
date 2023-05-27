#include "control.h"
#include <unordered_map>

Control::Control(uint8_t opcode)
{
  const static std::unordered_map<uint8_t, uint8_t> opcode_ctrl_map {
      { 0b0110011,   0b00100010 },    // R-type
      { 0b0010011,   0b10100010 },    // I-type
      { 0b0000011,   0b11110000 },    // LD
      { 0b0100011,   0b10001000 },    // SD
      { 0b1100011,   0b00000101 },    // Branch
  };

  uint8_t ctrl_bits = opcode_ctrl_map.at(opcode);

  alu_src     = (ctrl_bits >> 7) & 1;
  mem_to_reg  = (ctrl_bits >> 6) & 1;
  reg_write   = (ctrl_bits >> 5) & 1;
  mem_read    = (ctrl_bits >> 4) & 1;
  mem_write   = (ctrl_bits >> 3) & 1;
  branch      = (ctrl_bits >> 2) & 1;
  alu_op      = ctrl_bits & 0b11;
};
