#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <cstdint>

#define RAM_SZ      0x10000

extern uint8_t ram[RAM_SZ];
extern uint32_t ram_start;

int read_ram_u8(uint32_t addr, uint8_t *pval);
int read_ram_u16(uint32_t addr, uint16_t *pval);
int read_ram_u32(uint32_t addr, uint32_t *pval);
int read_ram(uint32_t addr, uint32_t *pval, uint8_t funct3);
int write_ram_u8(uint32_t addr, uint8_t val);
int write_ram_u16(uint32_t addr, uint16_t val);
int write_ram_u32(uint32_t addr, uint32_t val);
int write_ram(uint32_t addr, uint32_t val, uint8_t funct3);

#endif  // _MEMORY_H_
