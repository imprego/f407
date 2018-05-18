#include "stm32f4xx_hal.h"
#include "usb/usbd_def.h"
#include "usb/usbd_core.h"
#include "usb/usbd_desc.h"
#include "usb/usbd_cdc.h"
#include "usb/usbd_cdc_if.h"
#include "usb/usb.h"

#include "FreeRTOS.h"
#include "task.h"


USBD_HandleTypeDef hUsbDeviceFS;

void usb_init( void )
{
	USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS);
  USBD_RegisterClass(&hUsbDeviceFS, &USBD_CDC);
  USBD_CDC_RegisterInterface(&hUsbDeviceFS, &USBD_Interface_fops_FS);
  USBD_Start(&hUsbDeviceFS);
	return;
}


void usb_transmit( char* buf, unsigned short len )
{
	while( CDC_Transmit_FS( ( uint8_t* )buf, ( uint16_t )len ) != USBD_OK )
		vTaskDelay( 1 );
	return;
}

char* usb_receive( void )
{
	extern uint8_t UserRxBufferFS[];
	return ( char* )UserRxBufferFS;
}


void OTG_FS_IRQHandler( void )
{
	extern PCD_HandleTypeDef hpcd_USB_OTG_FS;
	HAL_PCD_IRQHandler( &hpcd_USB_OTG_FS );
	return;
}
