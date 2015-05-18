#ifndef _LMP91051_H
#define  _LMP91051_H



#define SDIO_EN_ADDR   		0X0F
#define DEVICE_CONFIG_ADDR	0X00
#define DAC_CONFIG_ADDR		0X01




#define P1_F_P2_F			0X00
#define P1_F_P2_O			0X01
#define P1_O_P2_F			0X10
#define P1_O_P2_O			0X11

#define FILT_ON				0X01
#define FILT_OFF			0x00
#define CMN_MODE_1			0
#define CMN_MODE_2			1

#define IN1					0
#define IN2					1

#define GAIN2_4				0X00
#define GAIN2_8				0X01
#define GAIN2_16			0X10
#define GAIN2_32			0X11

#define GAIN1_250			0X00
#define GAIN1_42			0x01



void spi_init(void) ;
void spi_write(unsigned char address,  unsigned char data_in);
unsigned char spi_read(unsigned char address);
void enable_sdio(void);
void disable_sdio(void);
void opa_init(void);


//extern unsigned char config_value ;

#endif

