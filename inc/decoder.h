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
  uint32_t    imm;
  mnemonic_t  mnemonic;
  format_t    format;

  Instruction() : opcode(0), rd(0), rs1(0), rs2(0), funct3(0), funct7(0), imm(0) {}
  void print();

private:
  std::unordered_map<format_t, std::string> _format_map {
    {R, "R"}, {I, "I"}, {S, "S"}, {B, "B"}, {U, "U"}, {J, "J"},
  };
  std::unordered_map<mnemonic_t, std::string> _mnemonic_map {
    { ADD,  "ADD" },
    { SUB,  "SUB" },
    { ADDI, "ADDI" },
    { AND,  "AND" },
    { OR,   "OR" },
    { XOR,  "XOR" },
    { ANDI, "ANDI" },
    { ORI,  "ORI" },
    { XORI, "XORI" },
    { BEQ,  "BEQ" },
    { LW,   "LW" },
    { SW,   "SW" },
    { SLL,  "SLL" },
    { SLLI, "SLLI" },
    { SRL,  "SRL" },
    { SRLI, "SRLI" },
    { SRA,  "SRA" },
    { SRAI, "SRAI" },
  };
};


Instruction decode(const std::string&);


#endif  // _DECODER_H_
