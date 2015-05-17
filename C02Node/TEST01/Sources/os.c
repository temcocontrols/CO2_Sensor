#include<string.h>
#include "IO_Map.h"
#include "AS2.h"
#include "os.h"
#include "extern.h"
#include "iic.h"
#include "htu21.h"
#include "PSENSOR.h"
#include "flash.h"
#include "caculate.h"
#include "modbus.h"
#include "aq.h"


static uint8_t task_ready_num = 0;
uint16_t task_tick[TASK_END];
uint8_t ready_task_queue[TASK_END];

//bit menu_start = FALSE;

uint16_t const  init_task_tick[TASK_END] =  // os tick = 10ms 
{
	200,		
	200,		
	300, 	
	500,
	300,
	100,
};

void task_init(void)
{
	uint8_t i;
	for(i = 0; i < TASK_END; i++)
	{
		task_tick[i] = init_task_tick[i];
	}
	task_ready_num = 0;
}

static void reset_task_tick(uint8_t task)
{
	task_tick[task] = init_task_tick[task];
}

static void push_task(uint8_t task)
{
	static uint8_t insert_queue_index = 0;
	if(insert_queue_index == TASK_END)
	{
		insert_queue_index = 0;
	}
	ready_task_queue[insert_queue_index++] = task;
	task_ready_num++;
}

static void run_routine(void)
{
	static uint8_t running_queue_index = 0;
	static  uint8_t beat_count = 0 ;  
	static uint8_t rever_heartled = 0 ;
	uint16_t co2_temp ;
	if(task_ready_num == 0)
	{
		return;
	}

	if(running_queue_index == TASK_END)
	{
		running_queue_index = 0;
	}

	switch(ready_task_queue[running_queue_index])
	{
		case TASK_OUTPUT:
			Press_Task();
		break;
		case TASK_HUM:
			HTU21_TASK();
		break;		
		case TASK_AQ:
			AD1_CreateSampleGroup(AdDataPTR, (LDD_ADC_TSample *)&ADC_AQ_Sample, 1U);
			AD1_StartSingleMeasurement(AdDataPTR);
			while(AD1_GetMeasurementCompleteStatus(AdDataPTR) != TRUE); 
			AD1_GetMeasuredValues(AdDataPTR, (LDD_TData *)&modbus.Aq_Ad)	;
			aq_analog_input = modbus.Aq_Ad /64;		
			check_Air_Quality();
//		if(rever_heartled)
//		{
//			GPIO1_SetFieldValue(GPIO1_Ptr, AQ_CTR, 1);
//			rever_heartled = 0 ;
//		}
//		else
//		{
//			GPIO1_ClearFieldBits(GPIO1_Ptr, AQ_CTR, 1);
//			rever_heartled = 1 ;
//		}
		break;
		case TASK_RTD:
			AD1_CreateSampleGroup(AdDataPTR, (LDD_ADC_TSample *)&ADC_TEMP_Sample, 1U);
			AD1_StartSingleMeasurement(AdDataPTR);
			while(AD1_GetMeasurementCompleteStatus(AdDataPTR) != TRUE); 
			AD1_GetMeasuredValues(AdDataPTR, (LDD_TData *)&modbus.Rtd_Ad)	;
		break;
		case TASK_FLASH: 
		write_to_flash();
		break;
		case TASK_CO2:
			if(modbus.co2_fac_cus_table == 0)
			{
			  co2_temp= Calculate(modbus.Co2_Ad, modbus.co2_fac_ad, modbus.co2_fac_ppm, modbus.co2_fac_point);
			  modbus.Co2= Filter(co2_temp ) ;
			}
////		else if(modbus.co2_fac_cus_table == 1) 
////			modbus.Co2 = Calculate(modbus.Co2_Ad, modbus.co2_cus_ad, modbus.co2_cus_ppm, modbus.co2_cus_point);	
		break;
		default:
		break;
	}
	reset_task_tick(ready_task_queue[running_queue_index]);
	running_queue_index++;
	task_ready_num--;
}

void task_manage(void)
{
	uint8_t task_index;
	for(task_index = 0; task_index < TASK_END; task_index++)
	{
		if(task_tick[task_index] > 0) 
		{			  
			task_tick[task_index]--;
			if(task_tick[task_index] == 0)
			{
				push_task(task_index);
			}
		}
	}

	run_routine();
}


