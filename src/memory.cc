#include <cstdio>
#include "memory.h"

int
read_ram_u8(uint32_t addr, uint8_t *pval)
{
  addr -= ram_start;
  if (addr >= RAM_SZ) {
    return 1;
  }
  *pval = ram[addr];
  return 0;
}

int
read_ram_u16(uint32_t addr, uint16_t *pval)
{
  addr -= ram_start;
  // TODO: sanity check misaligned addr
  if (addr+1 >= RAM_SZ) {
    return 1;
  }
  uint8_t *p = ram + addr;
  *pval = p[0] | (p[1] << 8);
  return 0;
}

int
read_ram_u32(uint32_t addr, uint32_t *pval)
{
  addr -= ram_start;
  // TODO: sanity check misaligned addr
  if (addr+3 >= RAM_SZ) {
    return 1;
  }
  uint8_t *p = ram + addr;
  *pval = p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
  return 0;
}

int
read_ram(uint32_t addr, uint32_t *pval, uint8_t funct3)
{
  int ret = 1;
  switch (funct3) {
    case 0x0:
      ret = read_ram_u8(addr, (uint8_t *)pval);
      break;
    case 0x1:
      ret = read_ram_u16(addr, (uint16_t *)pval);
      break;
    case 0x2:
      ret = read_ram_u32(addr, pval);
      break;
    default:
      puts("[ERR] read_ram: you shouldn't be here!");
  }
  return ret;
}

int
write_ram_u8(uint32_t addr, uint8_t val)
{
  addr -= ram_start;
  if (addr >= RAM_SZ) {
    return 1;
  }
  ram[addr] = val & 0xff;
  return 0;
}

int
write_ram_u16(uint32_t addr, uint16_t val)
{
  addr -= ram_start;
  if (addr+1 >= RAM_SZ) {
    return 1;
  }
  ram[addr]   = val         & 0xff;
  ram[addr+1] = (val >>  8) & 0xff;
  return 0;
}

int
write_ram_u32(uint32_t addr, uint32_t val)
{
  addr -= ram_start;
  if (addr+3 >= RAM_SZ) {
    return 1;
  }
  ram[addr]   = val         & 0xff;
  ram[addr+1] = (val >>  8) & 0xff;
  ram[addr+2] = (val >> 16) & 0xff;
  ram[addr+3] = (val >> 24) & 0xff;
  return 0;
}

int
write_ram(uint32_t addr, uint32_t val, uint8_t funct3)
{
  int ret = 1;
  switch (funct3) {
    case 0x0:
      ret = write_ram_u8(addr, val);
      break;
    case 0x1:
      ret = write_ram_u16(addr, val);
      break;
    case 0x2:
      ret = write_ram_u32(addr, val);
      break;
    default:
      puts("[ERR] write_ram: you shouldn't be here!");
  }
  return ret;
}
