
#include "extern.h"
#include "lmp91051.h"
#include "modbus.h"
#include "co2.h"
#define TOTAL_SAMPLE	5
#define DELAY_TIME		350

uint16_t lamp_count = 0 ;
uint8_t	 ad_count_start = 0 ;
uint16_t		ad_count = 0 ;


void Co2_Detect(void)
{
	static uint8_t lamp_on_off = 0 ;
	static uint8_t channel_switch = 0 ;
	static uint8_t detect_flag = 0 ;
	static uint8_t sample_count = 0 ;
	static uint32_t sum = 0 ;
	//uint8_t str[20] ;
	if(modbus.st_dectt == 0)  return ;
	if(lamp_count >= 500)
	{
			lamp_count = 0 ;
			if(lamp_on_off == 0)
			{
					lamp_on_off = 1 ;	
					if(channel_switch)
					{
							channel_switch = 0 ;
							spi_write(DEVICE_CONFIG_ADDR, 0x65) ;
					}
					else
					{
							channel_switch = 1 ;
							spi_write(DEVICE_CONFIG_ADDR, 0xe5) ;
					}
					GPIO1_SetFieldValue(GPIO1_Ptr, LAMP_CTR, 1); //turn on the lamp
					ad_count_start = 1 ;
					ad_count = 0 ;
			}
			else
			{
				ad_count_start = 0 ;
				ad_count	= 0 ;			
				lamp_on_off = 0 ;	//turn off the lamp
				GPIO1_ClearFieldBits(GPIO1_Ptr, LAMP_CTR, 1); //turn off the lamp
			}
	}
	if(ad_count >= DELAY_TIME )
	{
		ad_count_start =0 ;	
		ad_count = 0 ;
		  detect_flag = 1 ;
	}
	if(detect_flag == 1)
	{
			sample_count ++ ;
		  AD1_CreateSampleGroup(AdDataPTR, (LDD_ADC_TSample *)&ADC_CO2_Sample, 1U);
			AD1_StartSingleMeasurement(AdDataPTR);
			while(AD1_GetMeasurementCompleteStatus(AdDataPTR) != TRUE);
			if(channel_switch)
			{
				AD1_GetMeasuredValues(AdDataPTR, (LDD_TData *)&Test_Flag[1])	;
				sum += Test_Flag[1] ;
				if(sample_count== TOTAL_SAMPLE)
				{
					Test_Flag[2] = (uint16_t)(sum /TOTAL_SAMPLE) ;
					sample_count = 0 ;
					detect_flag = 0 ;
					sum = 0 ;
				}
			}
			else
			{
					AD1_GetMeasuredValues(AdDataPTR, (LDD_TData *)&Test_Flag[0])	;
					sum+= Test_Flag[0] ;
					if(sample_count== TOTAL_SAMPLE)
					{
						Test_Flag[3] = (uint16_t)(sum /TOTAL_SAMPLE) ;
						modbus.Co2_Ad = Test_Flag[2] - Test_Flag[3] ;  // co2 ad value
						sample_count = 0 ;
						detect_flag = 0 ;
						sum = 0 ;
					}
			}
		
//					AD1_CreateSampleGroup(AdDataPTR, (LDD_ADC_TSample *)&ADC_PM25_Sample, 1U);
//					AD1_StartSingleMeasurement(AdDataPTR);
//					while(AD1_GetMeasurementCompleteStatus(AdDataPTR) != TRUE); 
//					AD1_GetMeasuredValues(AdDataPTR, (LDD_TData *)&PM25_AD)	;
//					sprintf((void*)str, "P%u\n\r", (uint16_t)PM25_AD);
//				  AS2_SendBlock(AS2_ptr, str, strlen((const char*)str))  ;
//					Delay(2);
	}
	
}
