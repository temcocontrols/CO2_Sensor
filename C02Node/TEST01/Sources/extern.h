

#ifndef __EXTERN_H
#define __EXTERN_H

#include "string.h"
#include "stdio.h"
#include "IO_Map.h"
#include "GPIO1.h"
#include "GPIO2.h"
#include "AS2.h"
#include "AS1.h"
#include "AD1.h"
#include "Flash1.h"


#define USART_REV_LEN  			50  	//定义最大接收字节数 200
#define USART_SEND_LEN			250
#define SERIAL_RECEIVE_TIMEOUT  10


extern uint16_t Delay_count ;


extern LDD_TDeviceData *GPIO1_Ptr ;
extern LDD_TDeviceData *GPIO2_Ptr ;
extern AS2_TDeviceDataPtr *AS2_ptr;
extern AS1_TDeviceDataPtr *AS1_ptr;
////extern AD1_TDeviceDataPtr* Ad1_DeviceData ;
extern LDD_TDeviceData *AdDataPTR ;
extern LDD_ADC_TSample   ADC_PM25_Sample ;
extern LDD_ADC_TSample   ADC_AQ_Sample ;
extern LDD_ADC_TSample   ADC_TEMP_Sample  ;
extern LDD_ADC_TSample   ADC_CO2_Sample  ;
extern uint16_t 			PM25_AD  ;
extern uint16_t 			TEMP_AD  ;
extern uint16_t 			AQ_AD  ;
extern uint16_t 			CO2_AD  ;
extern uint8_t USART_RX_BUF[USART_REV_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
extern uint8_t serial_response_delay  ;
extern uint8_t rece_size  ;
extern uint8_t revce_count ;
extern uint8_t  print_position ;

extern uint8_t	heartbeat ; 


extern uint16_t lamp_count ;
extern uint8_t	 ad_count_start  ;
extern uint16_t		ad_count  ;

void Delay(uint16 delay_time) ;




#define WRITE_SN					0xc0
#define READ_SN						0xc1

#define READ_AQ					0x80

#define READ_PRESURE_PARAMETER		0x90


#define CLEAR_HUM_TABLE				0xa1
#define READ_HUM_TABLE				0xa3
#define READ_HUM_PARAMETER		0xa4



#define READ_CO2_PARAMETER        0xb0

#define REST_CMD                 	0xb1
#define READ_CO2_AD_CMD           0xb3

#define READ_CLIBRATION_CMD      	0xb5
#define CALIBRATION_RESET_CMD   	0xb6
#define STOP_DETECT               0xb7



#define READ_CO2_RTD_CMD			0xb9
#define READ_RTD_CAL_CMD      0xba
#define WRITE_RTD_CAL_CMD			0xbc
#define CLEAR_RTD_CAL_CMD			0xbf

#define TEMP_COMPENSATION_ON		0xbd
#define TEMP_COMPENSATION_OFF		0xbe


#define READ_ALL_PARAMETER			0xE0
#define READ_PM25								0xE1


extern uint8_t MODBUS_PROTOCOL  ;
extern uint16_t Test_Flag[10] ;
extern uint8_t As2_str[50]; 
extern LDD_TDeviceData * FlashDevice_ptr ;   

void Ram_Init(void) ;
void  flash_read(LDD_TDeviceData *DeviceDataPtr, LDD_FLASH_TAddress FromAddress, LDD_TData *ToPtr, LDD_FLASH_TDataSize Size) ;
void flash_write(LDD_TDeviceData *DeviceDataPtr, LDD_TData *FromPtr, LDD_FLASH_TAddress ToAddress, LDD_FLASH_TDataSize Size) ;

#endif
