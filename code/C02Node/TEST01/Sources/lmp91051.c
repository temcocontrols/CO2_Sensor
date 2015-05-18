#include "modbus.h"
#include "extern.h"
#include "lmp91051.h"

//uint8_t config_value = 0 ;


void spi_init(void)
{
	GPIO1_SetFieldOutputDirection(GPIO1_Ptr,CSB, 1);
	GPIO1_SetFieldOutputDirection(GPIO1_Ptr,SCLK, 1);
	GPIO1_SetFieldOutputDirection(GPIO1_Ptr, SDIO, 1);
	
}


void spi_write(uint8_t address,  uint8_t data_in)
{
	uint8_t i ;
	address = address & 0x0f ;
	GPIO1_SetFieldOutputDirection(GPIO1_Ptr,CSB, 0);
	i = 8 ;
	while(i--)
	{
		GPIO1_SetFieldOutputDirection(GPIO1_Ptr,SCLK, 0); 
		if((address>>i)&0x01) GPIO1_SetFieldOutputDirection(GPIO1_Ptr, SDIO, 1);
		else									 GPIO1_SetFieldOutputDirection(GPIO1_Ptr, SDIO, 0);	
		GPIO1_SetFieldOutputDirection(GPIO1_Ptr,SCLK, 1);
	}
	i = 8 ;
	while(i--)
	{
		GPIO1_SetFieldOutputDirection(GPIO1_Ptr,SCLK, 0);
		if((data_in>>i)&0x01) GPIO1_SetFieldOutputDirection(GPIO1_Ptr, SDIO, 1);
		else									 GPIO1_SetFieldOutputDirection(GPIO1_Ptr, SDIO, 0);			
		GPIO1_SetFieldOutputDirection(GPIO1_Ptr,SCLK, 1);
	}	
	GPIO1_SetFieldOutputDirection(GPIO1_Ptr,CSB, 1);
}

uint8_t spi_read(uint8_t address)
{
	uint8_t i ;
	uint8_t get_data = 0 ;
	address = address & 0x0f ;
	address = address |0x80 ;
	GPIO1_SetFieldOutputDirection(GPIO1_Ptr,CSB, 0);
	i = 8 ;
	while(i--)
	{
		GPIO1_SetFieldOutputDirection(GPIO1_Ptr,SCLK, 0);
//		SDIO = (address>>(i-1))&0x01; 
		if((address>>(i-1))&0x01) GPIO1_SetFieldOutputDirection(GPIO1_Ptr, SDIO, 1);
		else											 GPIO1_SetFieldOutputDirection(GPIO1_Ptr, SDIO, 0);
		GPIO1_SetFieldOutputDirection(GPIO1_Ptr,SCLK, 1);
	}
	GPIO1_SetFieldOutputDirection(GPIO1_Ptr, SDIO, 1);
	GPIO1_SetFieldInputDirection(GPIO1_Ptr, SDIO);
	i = 8 ;
	while(i--)
	{
		GPIO1_SetFieldOutputDirection(GPIO1_Ptr,SCLK, 0);
		GPIO1_SetFieldOutputDirection(GPIO1_Ptr,SCLK, 1);
		get_data = (get_data << 1) |GPIO2_GetFieldValue(GPIO2_Ptr, SDIO);
//		SCLK = 0 ;
//		SCLK = 1 ;
//		if(SDIO == 1)
//		get_data |= (1<<i) ;			
	}
		GPIO1_SetFieldOutputDirection(GPIO1_Ptr,CSB, 1);
	return get_data ;
}

void enable_sdio(void)
{
	spi_write(SDIO_EN_ADDR, 0XFE);
	spi_write(SDIO_EN_ADDR, 0XED);
}

void disable_sdio(void)
{
	spi_write(SDIO_EN_ADDR, 0XFF);
	spi_write(SDIO_EN_ADDR, 0XFF);
}
void opa_init(void)
{
	//config_value = (IN1<<7)|(P1_O_P2_O<<5)|(FILT_OFF<<4)|(CMN_MODE_1<<3)|(GAIN2_4<<1)|GAIN1_42 ;
	//config_value = 0x63 ;
	spi_write(DEVICE_CONFIG_ADDR, 0x65) ;
	spi_write(DAC_CONFIG_ADDR, 160) ;	//gain=1000, offset = 160  gain = 168 offset=175
}

//REGISTER	VALUE
// 001				168				161
//011				336				161
//101				672				160
//000				1000			159
//111				1344			159
//010				2000			157
//100				4000			153
//110				8000			146











