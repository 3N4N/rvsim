#ifndef _DECODER_H_
#define _DECODER_H_

#include <cstdint>
#include <string>
#include <unordered_map>

typedef enum {
  ADD, SUB, ADDI, AND, OR, XOR, ANDI, ORI, XORI, BEQ, LW, SW, SLL, SLLI, SRL,
  SRLI, SRA, SRAI,
} mnemonic_t;

typedef enum {
  R, I, S, B, U, J,
} format_t;

struct Instruction {
  uint8_t     opcode;
  uint8_t     rd;
  uint8_t     rs1;
  uint8_t     rs2;
  uint8_t     funct3;
  uint8_t     funct7;
  mnemonic_t  mnemonic;
  format_t    format;
  uint32_t    imm;

  void print();

private:
  std::unordered_map<format_t, std::string> format_map {
    {R, "R"}, {I, "I"}, {S, "S"}, {B, "B"}, {U, "U"}, {J, "J"},
  };
};


Instruction decode(const std::string&);


#endif  // _DECODER_H_
