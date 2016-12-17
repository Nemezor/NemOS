#ifndef HEADER_GDT
#define HEADER_GDT

#include "memory.h"
#include "asm_utils.h"

void gdt_setup_global_descriptor_table();
long long gdt_create_descriptor_entry(long base, long limit, short flags);

#endif

//                       protected mode GDT entry
// +-------------+-------+--------------+--------+------------+-------------+
// | base[24:31] | Flags | Limit[16:19] | Access | Base[0:23] | Limit[0:15] |
// +63---------56+55---52+51----------48+47----40+39--------16+15----------0+
//
//             Access byte
// +----+-------+---+----+----+----+----+
// | Pr | Privl | 1 | Ex | DC | RW | Ac |
// +7---+-------+---+----+----+----+---0+