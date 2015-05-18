#ifndef __MODBUS_H
#define	__MODBUS_H
#include "IO_Map.h"

#define	READ_VARIABLES				0x03
#define	WRITE_VARIABLES				0x06
#define	MULTIPLE_WRITE				0x10
#define	CHECKONLINE					0x19

#define DATABUFLEN					200
#define DATABUFLEN_SCAN				12
#define SENDPOOLLEN         		8





extern uint8_t serial_receive_timeout_count ; 

extern uint8_t dealwithTag ;


void serial_restart(void) ;
 void dealwithData(void) ;
void modbus_init(void) ;

void Response_Request(uint8_t cmd) ;







typedef struct 
{
	uint16_t serial_Num[2];
	uint16_t software ;
	uint8_t address ;
	uint16_t baudrate ;
	uint8_t	baud ;
	uint8_t update ;
	uint8_t product ;
	uint8_t hardware_Rev;
	uint8_t SNWriteflag ;
	
	uint16_t PM25 ;	
	uint16_t PM25_offset ;
	uint16_t Pm25_Ad ;
	
	uint16_t Co2 ;
	int16_t Co2_T ;
	uint16_t Co2_Ad ;
	uint8_t Compensation_On_Off ;
	int16_t Rtd ;
	uint16_t Rtd_Ad ;
	uint16_t Rtd_R ;
	uint16_t Rtd_Point ;
	uint16_t Rtd_Cal_Ad[2];
	uint16_t Rtd_Cal_T[2];

	uint16_t filter ;
	uint16_t Aq ;
	uint16_t Aq_Ad ;
	
	uint16_t	 Aq_offset ;

	uint16_t HH ;
	uint16_t HH_offset ;
	int16_t  HT ;
	uint16_t HT_offset ;
	uint8_t Hum_Cal_point ;

	uint16_t  Hum_MeterValue[10];
	uint16_t  Hum_SensorValue[10];
	uint16_t Rtd_Ref	;
	
	uint16_t co2_fac_point ;
	uint16_t co2_fac_ad[10] ;
	uint16_t co2_fac_ppm[10];
	uint16_t co2_cus_point ;
	uint16_t co2_cus_ad[10] ;
	uint16_t co2_cus_ppm[10];
	
	uint16_t co2_offset ;
	uint16_t st_dectt ;
	int16_t  PT  ;
	uint32_t PP;
	uint16_t PT_offset ;
	uint16_t co2_fac_cus_table ;
	
	uint16_t background_ppm ;
	uint16_t background_max_adj ;
	uint16_t backgroud_days ;
	uint16_t backgroud_time ;
	uint16_t auto_cal_on_off ;
	int16_t backgroud_offset ;
	
}STR_MODBUS ;
extern STR_MODBUS modbus ;






void urat_printf( char* send_buf, uint16_t len) ;





#endif
