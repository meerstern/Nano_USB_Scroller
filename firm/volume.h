#pragma once

#define VENDOR_ID	0xFE, 0xCA		// 0xCafe
#define PRODUCT_ID  0x23, 0x00		// 0x0023

#define MANUFACTURER_DESCRIPTION	\
	'C', 0x00, 'r', 0x00, 'e', 0x00, 's', 0x00, 'c', 0x00, 'e', 0x00, 'n', 0x00, 't', 0x00
	
#define PRODUCT_DESCRIPTION	\
	'N', 0x00, 'a', 0x00, 'n', 0x00, 'o', 0x00, ' ', 0x00, \
	'U', 0x00, 'S', 0x00, 'B', 0x00, ' ', 0x00, 'V', 0x00, 'o', 0x00, 'l', 0x00, 'u', 0x00, 'm', 0x00, 'e', 0x00


void USBInterruptHandler( void ) __interrupt (INT_NO_USB);
void volume_init();

void volumeUpHandle();
void volumeDownHandle();
void volumeMuteHandle();
void volumeResetHandle();
