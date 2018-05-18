#ifndef __USB_H
#define __USB_H

void usb_init( void );

void usb_transmit( char* buf, unsigned short len );
char* usb_receive( void );

#endif /* __USB_H */
