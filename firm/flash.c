#include <stdint.h>
#include "ch554.h"


void readDataFlash(unsigned char  Addr, unsigned char *buf, unsigned char len)
{
    unsigned char  i;
    ROM_ADDR_H = DATA_FLASH_ADDR >> 8;
    Addr <<= 1;
    for(i=0;i<len;i++)
	{
	  ROM_ADDR_L = Addr + i*2;
	  ROM_CTRL = ROM_CMD_READ;
	  *(buf+i) = ROM_DATA_L;
	}
}

void writeDataFlash(unsigned char Addr, unsigned char *buf, unsigned char len)
{
    unsigned char i;
    SAFE_MOD = 0x55;
    SAFE_MOD = 0xAA;
    GLOBAL_CFG |= bDATA_WE;
    SAFE_MOD = 0;
	ROM_ADDR_H = DATA_FLASH_ADDR >> 8;
    Addr <<= 1;
    for(i=0;i<len;i++)
	{
        ROM_ADDR_L = Addr + i*2;
        ROM_DATA_L = *(buf+i);			
        if ( ROM_STATUS & bROM_ADDR_OK )
		{ 
           ROM_CTRL = ROM_CMD_WRITE;
        }
        if((ROM_STATUS ^ bROM_ADDR_OK) > 0)
			return;
	}
    SAFE_MOD = 0x55;
    SAFE_MOD = 0xAA;
    GLOBAL_CFG &= ~bDATA_WE;
    SAFE_MOD = 0;	
    return;		
}