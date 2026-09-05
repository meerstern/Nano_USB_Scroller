#pragma once

#define VENDOR_ID	0xFE, 0xCA		// 0xCafe
#define PRODUCT_ID  0x23, 0x00		// 0x0023

#define MANUFACTURER_DESCRIPTION	\
	'C', 0x00, 'r', 0x00, 'e', 0x00, 's', 0x00, 'c', 0x00, 'e', 0x00, 'n', 0x00, 't', 0x00
	
#define PRODUCT_DESCRIPTION	\
	'N', 0x00, 'a', 0x00, 'n', 0x00, 'o', 0x00, ' ', 0x00, \
	'U', 0x00, 'S', 0x00, 'B', 0x00, ' ', 0x00, 'M', 0x00, 'o', 0x00, 'u', 0x00, 's', 0x00, 'e', 0x00

#define MOUSE_LEFT_BUTTON	0b00000001
#define MOUSE_RIGHT_BUTTON	0b00000010
#define MOUSE_MIDDLE_BUTTON	0b00000100
#define MOUSE_BUTTONS_MASK	0b00000111

void USBInterruptHandler( void ) __interrupt (INT_NO_USB);
void mouse_init();
void hidValueHandle(uint8_t button, int8_t x, int8_t y, int8_t wheel);
