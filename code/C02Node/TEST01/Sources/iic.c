#include "extern.h"

#include "iic.h"
#define DELAY_TIME 1

//#define I2C_DELAY  5
static uint16_t i2c_delay ;

void iic_init(void)
{
	GPIO2_SetFieldBits(GPIO2_Ptr, I2C_DAT,  1) ;
	GPIO2_SetFieldBits(GPIO2_Ptr, I2C_CLK,  1) ;
}

uint8_t iic_readbyte(uint8_t ack)
{
	uint8_t temp = 0;
	uint8_t i;
	

	GPIO2_ClearFieldBits(GPIO2_Ptr, I2C_CLK,  1) ;
	GPIO2_SetFieldBits(GPIO2_Ptr, I2C_DAT,  1) ;
	GPIO2_SetFieldInputDirection(GPIO2_Ptr, I2C_DAT);
	for(i = 0; i < 8; i++)
	{
		GPIO2_SetFieldBits(GPIO2_Ptr, I2C_CLK,  1) ;
		for(i2c_delay =DELAY_TIME; i2c_delay>0; i2c_delay--); // Delay
		temp = (temp << 1) |GPIO2_GetFieldValue(GPIO2_Ptr, I2C_DAT);
		GPIO2_ClearFieldBits(GPIO2_Ptr, I2C_CLK,  1) ;
		for(i2c_delay =DELAY_TIME; i2c_delay>0; i2c_delay--); // Delay
	}
	
	if(ack == d_ACK)
	GPIO2_SetFieldOutputDirection(GPIO2_Ptr, I2C_DAT, 0);
	else
	GPIO2_SetFieldOutputDirection(GPIO2_Ptr, I2C_DAT, 1);
	
	GPIO2_SetFieldBits(GPIO2_Ptr, I2C_CLK,  1) ;
	GPIO2_ClearFieldBits(GPIO2_Ptr, I2C_CLK,  1) ;	
	return temp;
}
 
uint8_t iic_writebyte(uint8_t dat)
{
	uint8_t ack;
	uint8_t i = 8;
	do
	{    
		if(dat & 0x80)
		GPIO2_SetFieldOutputDirection(GPIO2_Ptr, I2C_DAT,  1);
		else
		GPIO2_SetFieldOutputDirection(GPIO2_Ptr, I2C_DAT,  0);	
		for(i2c_delay =DELAY_TIME; i2c_delay>0; i2c_delay--); // Delay
		GPIO2_SetFieldOutputDirection(GPIO2_Ptr, I2C_CLK,  1);		
		dat <<= 1;
		for(i2c_delay =DELAY_TIME; i2c_delay>0; i2c_delay--); // Delay
		GPIO2_SetFieldOutputDirection(GPIO2_Ptr, I2C_CLK,  0);
		for(i2c_delay =DELAY_TIME; i2c_delay>0; i2c_delay--); // Delay
	}while(--i != 0);
	GPIO2_SetFieldOutputDirection(GPIO2_Ptr, I2C_DAT,  1);
	GPIO2_SetFieldInputDirection(GPIO2_Ptr, I2C_DAT); 
	GPIO2_SetFieldOutputDirection(GPIO2_Ptr, I2C_CLK,  1);
	for(i2c_delay =DELAY_TIME; i2c_delay>0; i2c_delay--); // Delay
	ack = GPIO2_GetFieldValue(GPIO2_Ptr, I2C_DAT);
	GPIO2_SetFieldOutputDirection(GPIO2_Ptr, I2C_CLK,  0);	
	
	return ack;
}
uint8_t iic_start(uint8_t device_id)
{
	GPIO2_SetFieldOutputDirection(GPIO2_Ptr, I2C_DAT,  1);
	for(i2c_delay =DELAY_TIME; i2c_delay>0; i2c_delay--); // Delay
	GPIO2_SetFieldOutputDirection(GPIO2_Ptr, I2C_CLK,  1);
	for(i2c_delay =DELAY_TIME; i2c_delay>0; i2c_delay--); // Delay
	GPIO2_SetFieldOutputDirection(GPIO2_Ptr, I2C_DAT,  0);
	for(i2c_delay =DELAY_TIME; i2c_delay>0; i2c_delay--); // Delay
	GPIO2_SetFieldOutputDirection(GPIO2_Ptr, I2C_CLK,  0);
	for(i2c_delay =DELAY_TIME; i2c_delay>0; i2c_delay--); // Delay
	iic_writebyte(device_id);
	
	return 0 ;
}

uint8_t iic_restart(uint8_t device_id)
{
	iic_start(device_id);
	return 0 ;
}

void iic_stop(void)
{
	GPIO2_SetFieldOutputDirection(GPIO2_Ptr, I2C_DAT,  0);
	for(i2c_delay =DELAY_TIME; i2c_delay>0; i2c_delay--); // Delay
	GPIO2_SetFieldOutputDirection(GPIO2_Ptr, I2C_CLK,  1);
	for(i2c_delay =DELAY_TIME; i2c_delay>0; i2c_delay--); // Delay
	GPIO2_SetFieldOutputDirection(GPIO2_Ptr, I2C_DAT,  1);
}


//void iic_stop(void)
//{
//	IIC_SDA = 0;
//	delay_us(I2C_DELAY);
//	IIC_SCL = 1;
//	delay_us(I2C_DELAY);
//	IIC_SDA = 1;
//}

// 
//uint8 iic_writebyte(uint8 dat)
//{
//	uint8 ack;
//	uint8 i = 8;
//	do
//	{    
//		IIC_SDA = dat & 0x80;
//		IIC_SCL = 1;
//		delay_us(I2C_DELAY);
//		dat <<= 1;
//		IIC_SCL = 0;
//		delay_us(I2C_DELAY);
//	}while(--i != 0);

//	IIC_SDA = 1;
//	delay_us(I2C_DELAY);
//	IIC_SCL = 1;
//	ack = IIC_SDA;
//	delay_us(I2C_DELAY);
//	IIC_SCL = 0;
//	return ack;
//}

//bit iic_start(uint8 device_id)
//{
////	IIC_SCL = 0;
//	IIC_SDA = 1;
//	delay_us(I2C_DELAY);
//	IIC_SCL = 1;
//	delay_us(I2C_DELAY);
//	IIC_SDA = 0;
//	delay_us(I2C_DELAY);
//	IIC_SCL = 0;
//	delay_us(I2C_DELAY);
//	iic_writebyte(device_id);
//	return 0 ;
//}

//bit iic_restart(uint8 device_id)
//{
//	iic_start(device_id);
//	return 0 ;
//}
//void iic_stop(void)
//{
//	IIC_SDA = 0;
//	delay_us(I2C_DELAY);
//	IIC_SCL = 1;
//	delay_us(I2C_DELAY);
//	IIC_SDA = 1;
//}
