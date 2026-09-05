#pragma once

#include <stdint.h>
#include "ch554.h"

void readDataFlash(unsigned char  Addr, unsigned char *buf, unsigned char len);
void writeDataFlash(unsigned char Addr, unsigned char *buf, unsigned char len);
