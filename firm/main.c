#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "debug.h"

#include "ch554.h"
#include "mouse.h"
#include "flash.h"

#define ADDRESS_DIRECTION	0		//Flash Address for Direction Memory

#define ENC_A_PIN		4	//IN
#define ENC_B_PIN		5	//IN
#define CENTER_SW_PIN	6	//IN

#define delayUs	mDelayuS

enum
{
	FORWARD_DIR_MODE,
	REVERSE_DIR_MODE
};

SBIT(ENC_A, 	0x90, ENC_A_PIN);
SBIT(ENC_B, 	0x90, ENC_B_PIN);
SBIT(CENTER_SW, 0x90, CENTER_SW_PIN);

static bool centerSwOld = true;

static uint8_t encoder_state;
static short encoder_delta = 0;
static short encoder_delta_old = 0;
static uint8_t dirMode = FORWARD_DIR_MODE;


void gpio_interrupt(void) __interrupt(INT_NO_GPIO)
{
	uint8_t state;
	uint8_t transition;

    // Get P1.4/P1.5 
    state = (P1 >> 4) & 0x03;
   
    // Old -> Now
    transition = (encoder_state << 2) | state;

    switch (transition)
    {        
        case 0x01:  // 00 -> 01
        case 0x07:  // 01 -> 11
        case 0x0E:  // 11 -> 10
        case 0x08:  // 10 -> 00
            encoder_delta++;
            break;

        case 0x02:  // 00 -> 10
        case 0x0B:  // 10 -> 11
        case 0x0D:  // 11 -> 01
        case 0x04:  // 01 -> 00
            encoder_delta--;
            break;

        default:
            break;
    }

    encoder_state = state;	
}

void initGPIO(void)
{	
	//Input Pullup
	P1_MOD_OC &= ~(1 << ENC_A_PIN);
    P1_DIR_PU |= (1<<ENC_A_PIN);	
	
	P1_MOD_OC &= ~(1 << ENC_B_PIN);
    P1_DIR_PU |= (1<<ENC_B_PIN);	
	
	P1_MOD_OC &= ~(1 << CENTER_SW_PIN);
    P1_DIR_PU |= (1<<CENTER_SW_PIN);	
}


void enableInterruptGPIO()
{
	GPIO_IE &= ~bIE_IO_EDGE; 
	GPIO_IE |= bIE_P1_4_LO;
	GPIO_IE |= bIE_P1_5_LO;
	//GPIO_IE |= bIE_RXD1_LO;//P1.6
	IE_GPIO  = 1; 
	//IE_EX |= IE_GPIO;
	EA = 1;
}


void main()
{
	CfgFsys();
	mInitSTDIO();
	initGPIO();
	enableInterruptGPIO();
	
	unsigned char direction = FORWARD_DIR_MODE;
	readDataFlash(ADDRESS_DIRECTION, &direction, 1);
	if(CENTER_SW == 0)//Pushed
	{
		if(direction == REVERSE_DIR_MODE)
			direction = FORWARD_DIR_MODE;
		else
			direction = REVERSE_DIR_MODE;
		
		writeDataFlash(ADDRESS_DIRECTION, &direction, 1);	
	}
	
	mouse_init();

	while(1)
	{
		bool centerSw = CENTER_SW;
		if( encoder_delta!=encoder_delta_old && abs(encoder_delta-encoder_delta_old)<100  && abs(encoder_delta-encoder_delta_old) > 1 
			|| centerSw!=centerSwOld)
		{
			
			uint8_t button = (CENTER_SW==0)?MOUSE_MIDDLE_BUTTON:0;
			int8_t wheel = encoder_delta;
			if(direction == REVERSE_DIR_MODE)
				wheel = -1*wheel;
			hidValueHandle(button, 0, 0, wheel);			
			//printf("Val: %d\n",encoder_delta);
			encoder_delta = 0;
			encoder_delta_old = encoder_delta;
			centerSwOld = centerSw;	
			mDelaymS(5);			
		}		
	}
}
