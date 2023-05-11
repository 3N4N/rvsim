#ifndef _ALU_H_
#define _ALU_H_

#include "util.h"

/// ALU
///
/// Param 'aluop' is a 4-bit binary string consisting of
/// the 5th bit of funct7 in its MSB and 3 bits of funct3
/// Use: (funct7>>2) | funct3
uint32_t alu(uint32_t rd1, uint32_t rd2, uint8_t aluop);

#endif  // _ALU_H_
