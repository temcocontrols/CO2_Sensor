/* ###################################################################
**     Filename    : main.c
**     Project     : TEST01
**     Processor   : MKL15Z32VLK4
**     Version     : Driver 01.01
**     Compiler    : Keil ARM C/C++ Compiler
**     Date/Time   : 2015-04-16, 10:53, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


#include <string.h>
#include <stdio.h>

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "AD1.h"
#include "AS1.h"

#include "GPIO1.h"
#include "UART0_PDD.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "TU1.h"
#include "Flash1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "extern.h"
#include "modbus.h"
#include "os.h"
#include "PSENSOR.h"
#include "lmp91051.h"
#include "co2.h"
#include "flash.h"
#include "aq.h"

 uint16_t 			PM25_AD  ;
 uint16_t 			TEMP_AD  ;
 uint16_t 			AQ_AD  ;
 uint16_t 			CO2_AD  ;

AS1_TDeviceDataPtr *AS1_ptr;
AS2_TDeviceDataPtr *AS2_ptr;
LDD_TDeviceData * FlashDevice_ptr ;
LDD_TDeviceData *GPIO1_Ptr ;
LDD_TDeviceData *GPIO2_Ptr ;
//AD1_TDeviceDataPtr	AD_dataptr ;	
uint16_t Delay_count ;

uint8_t	heartbeat ; 
uint8_t heartbeat_counter = 0;


/* User includes (#include below this line is not maintained by Processor Expert) */

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
	uint8_t i ;
	//uint8_t send_buf[50] ;
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/

  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
	GPIO1_ClearFieldBits(GPIO1_Ptr, LAMP_CTR, 1); //turn off the lamp
	
	modbus_init();
	Ram_Init();
	read_from_flash();
	task_init();
	bmp180_init();
	opa_init();
	Aq_Init();
  /* Write your code here */
  /* For example: */		
	for(;;) 
	{
//         sprintf((char*)send_buf,"#C%05u P%07u TP%04d TH%04d H%04u AQ%04u\n\r", modbus.Co2, modbus.PP, modbus.PT, modbus.HT, modbus.HH, modbus.Aq);
//         AS1_SendBlock(AS1_ptr, send_buf, strlen((char*)send_buf))  ;		
//				Delay(6);		
		if(heartbeat == TRUE)			//tick = 1ms
		{
			
			heartbeat = FALSE;

			if(serial_receive_timeout_count > 0)
			{
				serial_receive_timeout_count--;	
				if(serial_receive_timeout_count == 0)
				{
					revce_count = 0;
				}
			}

			if(serial_response_delay > 0)
				serial_response_delay--;
	
			if((dealwithTag == TRUE) && (serial_response_delay == 0))
			{	
				dealwithTag = FALSE;
				dealwithData();	
			}

			heartbeat_counter++;
			if(heartbeat_counter >= OS_TICK) // 1 * 10 = 10ms
			{
				heartbeat_counter = 0;
				task_manage();
			}
		}
		Co2_Detect();

		

		
//		
//					AS2_SendBlock(AS2_ptr, "start\n\r", sizeof("start\n\r"))  ;

//					print_status = AD1_CreateSampleGroup(AdDataPTR, &ADC_CO2_Sample,  1) ;	
//					Delay(300);
//					
//					sprintf((void*)str, "P = %u\n\r", (uint16_t)print_status);
//				  AS1_SendBlock(AS1_ptr, str, sizeof(str))  ;
//					Delay(300);
//			   if(enter_adc)
//					{
//							enter_adc = 0 ;
//							AS2_SendBlock(AS2_ptr, "enteradc\n\r", sizeof("enteradc\n\r"))  ;
//					}
//		      Delay(300);
//		switch(print_status)
//		{
//			case ERR_PARAM_SAMPLE_COUNT:
//				AS2_SendBlock(AS2_ptr, "Para\n\r", sizeof("Para\n\r"))  ;
//				break;
//			case ERR_BUSY:
//				AS2_SendBlock(AS2_ptr, "BSY\n\r", sizeof("BSY\n\r"))  ;
//				break; 
//			case ERR_OK:
//				AS2_SendBlock(AS2_ptr, "OK\n\r", sizeof("OK\n\r"))  ;
//				break ;
//						case ERR_PARAM_INDEX:
//				AS2_SendBlock(AS2_ptr, "index\n\r", sizeof("index\n\r"))  ;
//				break ;
//		}					
//					AD1_CreateSampleGroup(AdDataPTR, (LDD_ADC_TSample *)&ADC_PM25_Sample, 1U);
//					AD1_StartSingleMeasurement(AdDataPTR);
//					while(AD1_GetMeasurementCompleteStatus(AdDataPTR) != TRUE); 
//					AD1_GetMeasuredValues(AdDataPTR, (LDD_TData *)&PM25_AD)	;
//					sprintf((void*)str, "P%u\n\r", (uint16_t)PM25_AD);
//				  AS1_SendBlock(AS1_ptr, str, strlen((const char*)str))  ;
//					Delay(3000) ;

	} 
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.4 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/








void Delay(uint16 delay_time)
{
	Delay_count = delay_time ;
	while(Delay_count);
}

void Ram_Init(void)
{	
	uint8_t  str[20] ;
	uint16_t temp = 0x1234 ;
//	flash_write(FlashDevice_ptr, &temp,  0x7c00, 2) ;
//	flash_read(FlashDevice_ptr, 0x7c00, &CO2_AD, 2);
//	Delay(20) ;
//	sprintf((char*)str, "CO2_AD =%u\n\r", CO2_AD);
//	AS2_SendBlock(AS2_ptr, str, strlen((char*)str))  ;
	Delay(20) ;

}




