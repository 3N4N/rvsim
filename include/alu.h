#pragma once

#include "util.h"

uint8_t get_alu_ctrl(uint8_t alu_op, uint8_t funct3, uint8_t funct7);
uint32_t alu(uint32_t rd1, uint32_t rd2, uint8_t alu_ctrl);
