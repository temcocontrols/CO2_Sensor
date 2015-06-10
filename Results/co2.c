
#include "extern.h"
#include "lmp91051.h"
#include "modbus.h"
#include "co2.h"
#define TOTAL_SAMPLE	5
#define DELAY_TIME		350
#define SAMPLE_NUM		250


uint8_t A2_P[15];

uint16_t lamp_count = 0 ;
uint8_t	 ad_count_start = 0 ;
//uint16_t		ad_count = 0 ;
uint8_t	 ad_switch_count = 0 ;
uint8_t 	lamp_on_off = 0 ;

uint16_t Ref_ad ; 
uint16_t Act_ad ;
uint16_t Ad_diff ;
uint8_t turn_on_lamp = 0 ;
uint8_t turn_off_lamp = 0 ;
uint8_t record_flag = 0 ;


static uint16_t P_out_flag = 0 ;
uint16_t P_out[1000] ;

uint16_t active_value ;
uint16_t ref_value     ;

//void Co2_Detect(void)
//{
//	static uint8_t lamp_on_off = 0 ;
//	static uint8_t channel_switch = 0 ;
//	static uint8_t detect_flag = 0 ;
//	static uint8_t sample_count = 0 ;
//	static uint32_t sum = 0 ;
//	//uint8_t str[20] ;
//	if(modbus.st_dectt == 0)  return ;
//	if(lamp_count >= 500)
//	{
//			lamp_count = 0 ;
//			if(lamp_on_off == 0)
//			{
//					lamp_on_off = 1 ;	
//					if(channel_switch)
//					{
//							channel_switch = 0 ;
//							spi_write(DEVICE_CONFIG_ADDR, 0x65) ;
//					}
//					else
//					{
//							channel_switch = 1 ;
//							spi_write(DEVICE_CONFIG_ADDR, 0xe5) ;
//					}
//					GPIO1_SetFieldValue(GPIO1_Ptr, LAMP_CTR, 1); //turn on the lamp
//					ad_count_start = 1 ;
//					ad_count = 0 ;
//			}
//			else
//			{
//				ad_count_start = 0 ;
//				ad_count	= 0 ;			
//				lamp_on_off = 0 ;	//turn off the lamp
//				GPIO1_ClearFieldBits(GPIO1_Ptr, LAMP_CTR, 1); //turn off the lamp
//			}
//	}
//	if(ad_count >= DELAY_TIME )
//	{
//		ad_count_start =0 ;	
//		ad_count = 0 ;
//		  detect_flag = 1 ;
//	}
//	if(detect_flag == 1)
//	{
//			sample_count ++ ;
//		  AD1_CreateSampleGroup(AdDataPTR, (LDD_ADC_TSample *)&ADC_CO2_Sample, 1U);
//			AD1_StartSingleMeasurement(AdDataPTR);
//			while(AD1_GetMeasurementCompleteStatus(AdDataPTR) != TRUE);
//			if(channel_switch)
//			{
//				AD1_GetMeasuredValues(AdDataPTR, (LDD_TData *)&Test_Flag[1])	;
//				sum += Test_Flag[1] ;
//				if(sample_count== TOTAL_SAMPLE)
//				{
//					Test_Flag[2] = (uint16_t)(sum /TOTAL_SAMPLE) ;
//					sample_count = 0 ;
//					detect_flag = 0 ;
//					sum = 0 ;
//				}
//			}
//			else
//			{
//					AD1_GetMeasuredValues(AdDataPTR, (LDD_TData *)&Test_Flag[0])	;
//					sum+= Test_Flag[0] ;
//					if(sample_count== TOTAL_SAMPLE)
//					{
//						Test_Flag[3] = (uint16_t)(sum /TOTAL_SAMPLE) ;
//						modbus.Co2_Ad = Test_Flag[2] - Test_Flag[3] ;  // co2 ad value
//						sample_count = 0 ;
//						detect_flag = 0 ;
//						sum = 0 ;
//					}
//			}
//		
//	}
//	
//}

void Co2_Detect(void)
{
	
	 uint32_t sum = 0 ;
	static uint8_t co2_channel = 0 ;
	static uint8_t ad_detect_flag = 0 ;
	
	
	static uint8_t diff_count =0 ;
	static uint8_t turn_on = 0 ;
	static uint8_t ad_diff_time = 0 ;
	static uint32_t ad_diff_sum = 0 ;
	uint16_t loop = 0 ;
	uint16_t ad_temp ;
	uint16_t min = 0xffff ;
	uint16_t max = 0 ;
	uint16_t i ;

	static uint16_t P_out_count  = 0 ;
	
	
	if(modbus.st_dectt == 0)  return ;

	GPIO1_SetFieldValue(GPIO1_Ptr, LAMP_CTR, 1); //turn on the lamp

	for(loop=0; loop<500; loop++)
	{
			if(loop%2)
			{
				spi_write(DEVICE_CONFIG_ADDR, 0xe3) ;
			}
			else
			{
				spi_write(DEVICE_CONFIG_ADDR, 0x63) ;
						
			}
			for(i=0;i<4000;i++); //Delay
			P_out_count++ ;
			AD1_CreateSampleGroup(AdDataPTR, (LDD_ADC_TSample *)&ADC_CO2_Sample, 1U);
			AD1_StartSingleMeasurement(AdDataPTR);
			while(AD1_GetMeasurementCompleteStatus(AdDataPTR) != TRUE);
			AD1_GetMeasuredValues(AdDataPTR, (LDD_TData *)&ad_temp)	;
			P_out[loop] = ad_temp ;
	}
	GPIO1_ClearFieldBits(GPIO1_Ptr, LAMP_CTR, 1); //turn off the lamp
	if(P_out_count == 500)
	{
		P_out_flag = 1 ;
		P_out_count = 0 ;
	}
		
}

void print_out(void)
{
	static uint16_t print_loop = 0;	
	static uint8_t print_count = 0 ;
	uint16_t buf_arry[250] ;
	uint16_t i ;
	if((P_out_flag == TRUE)&&(record_flag == TRUE))
	{	
		/******************************FFT MATH*******************************/
		// 250 reference data and 250 active data is store in the P_out array.
		
//		return_value = fft(char* buf_addrss) ;
		
		for(i=0; i<SAMPLE_NUM; i++)
		{
			buf_arry[i] = 	P_out[2*i] ;  //
		}		
		//active_value = fft(buf_arry) ;
		active_value = FFT_CO2(buf_arry) ;
		
		for(i=0; i<SAMPLE_NUM; i++)
		{
			buf_arry[i] = 	P_out[2*i+1] ;
		}	
		ref_value = FFT_CO2( buf_arry) ;
		
		
/******************************print out data***************************/		
//		if(print_loop == 0)
//		sprintf((char*)A2_P, "%05u %05u %3u %3u\n\r ", P_out[print_loop],P_out[print_loop+1], modbus.HH, modbus.HT);//P_out[print_loop]
//		else
//		sprintf((char*)A2_P, "%05u %05u\n\r ", P_out[print_loop],P_out[print_loop+1]);//P_out[print_loop]
//		
//		AS1_SendBlock(AS1_ptr, A2_P, strlen(A2_P));
//		print_loop =print_loop+2 ;
//		if(print_loop >= 500)
//		{
//				//AS1_SendBlock(AS1_ptr, "\n\r", strlen("\n\r"));
//				print_loop = 0 ;
//				P_out_flag = 0 ;
//				print_count++ ;
//				if(print_count == 5)
//				{
//						record_flag = 0; 
//				}
//		}
	}
}
