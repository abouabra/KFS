#ifndef PORTS_H
#define PORTS_H

#include "kfs_def.h"

void outb(u16int port, u8int value);
u8int inb(u16int port);
u16int inw(u16int port);

#endif
