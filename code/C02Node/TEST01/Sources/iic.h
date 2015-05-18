#ifndef _IIC_H
#define _IIC_H
#include "IO_Map.h"


#define d_IIC_EN			0x80
//#define d_DEVICE_ID			0x50

#define d_IIC_MASTER		0x20
#define d_IIC_SLAVE			0x00
#define d_IIC_MODE_SEL		d_IIC_MASTER

#define d_IIC_ADR_CA1		0x00
#define d_IIC_ADR_CA2		0x10
#define d_MSK_IICCTL_MAS	0x10
#define d_IIC_ADR_SEL		d_IIC_ADR_CA2

#define d_BR32				0x00
#define d_BR64				0x01
#define d_BR128				0x02
#define d_BR256				0x03
#define d_BR512				0x04
#define d_BR1024			0x05
#define d_BR2048			0x06
#define d_BR4096			0x07
#define d_IIC_BR			d_BR512


//#define d_NACK				1
//#define d_ACK				0


#define d_NACK				0
#define d_ACK				1
#define d_WRITE				0
#define d_READ				1


void iic_init(void);
uint8_t iic_start(uint8_t device_id);
uint8_t iic_restart(uint8_t device_id);
uint8_t iic_readbyte(uint8_t ack)	;
uint8_t iic_writebyte(uint8_t dat);
void iic_stop(void);
uint8_t iic_readbyte(uint8_t ack);
uint8_t iic_writebyte(uint8_t dat);
















#endif

