#include "flash.h"
#include "modbus.h"
#include "registerlist.h"

uint8_t flash_change = 0 ;
void flash_write(LDD_TDeviceData *DeviceDataPtr, LDD_TData *FromPtr, LDD_FLASH_TAddress ToAddress, LDD_FLASH_TDataSize Size)
{
	LDD_FLASH_TOperationStatus  OpStatus;
	FLASH1_Write(DeviceDataPtr, FromPtr,  ToAddress, Size) ;
		do {
		FLASH1_Main(DeviceDataPtr);
		OpStatus = FLASH1_GetOperationStatus(DeviceDataPtr);
		} while (!((OpStatus == LDD_FLASH_IDLE) | (OpStatus == LDD_FLASH_FAILED)));
}

void  flash_read(LDD_TDeviceData *DeviceDataPtr, LDD_FLASH_TAddress FromAddress, LDD_TData *ToPtr, LDD_FLASH_TDataSize Size)
{
	LDD_FLASH_TOperationStatus  OpStatus;
	FLASH1_Read(DeviceDataPtr, FromAddress, ToPtr, Size);
	do {
	FLASH1_Main(DeviceDataPtr);
	OpStatus = FLASH1_GetOperationStatus(DeviceDataPtr);
	} while (!((OpStatus == LDD_FLASH_IDLE) | (OpStatus == LDD_FLASH_FAILED)));
}

uint16_t flash_erase(LDD_TDeviceData *DeviceDataPtr, LDD_FLASH_TAddress FromAddress, LDD_FLASH_TDataSize page)
{
	LDD_FLASH_TOperationStatus  OpStatus;
	uint16_t erase_status = 0 ;
	erase_status = FLASH1_Erase(DeviceDataPtr, FromAddress,  1024);
	do {
	FLASH1_Main(DeviceDataPtr);
	OpStatus = FLASH1_GetOperationStatus(DeviceDataPtr);
	} while (!((OpStatus == LDD_FLASH_IDLE) | (OpStatus == LDD_FLASH_FAILED)));
	return erase_status ;
}


void read_from_flash(void)
{
	uint8_t i ; 
	uint16_t read_temp ;
	for(i=0; i<10; i++)
	{
		flash_read(FlashDevice_ptr, EEP_FAC_CO2_CAL_AD1+4*i, &modbus.co2_fac_ad[i], 2);
		flash_read(FlashDevice_ptr, EEP_FAC_CO2_CAL_PPM1+4*i, &modbus.co2_fac_ppm[i], 2);
		flash_read(FlashDevice_ptr, EEP_CUS_CO2_CAL_AD1+4*i, &modbus.co2_cus_ad[i], 2);
		flash_read(FlashDevice_ptr, EEP_CUS_CO2_CAL_PPM1+4*i, &modbus.co2_cus_ppm[i], 2);
		flash_read(FlashDevice_ptr, EEP_HUM_METER0+4*i, &modbus.Hum_MeterValue[i], 2);
		flash_read(FlashDevice_ptr, EEP_HUM_SENSOR0+4*i, &modbus.Hum_SensorValue[i], 2);
		
		if((modbus.co2_fac_ad[i] == 0xffff)&&(modbus.co2_fac_ppm[i] == 0xffff))
		{
				modbus.co2_fac_ad[i] = 0 ;
				modbus.co2_fac_ppm[i] = 0 ;
				flash_change = 1 ;		
		}
		if((modbus.co2_cus_ad[i] == 0xffff)&&(modbus.co2_cus_ppm[i] == 0xffff))
		{
				modbus.co2_cus_ad[i] = 0 ;
				modbus.co2_cus_ppm[i] = 0 ;
				flash_change = 1 ;		
		}
		if((modbus.Hum_MeterValue[i] == 0xffff)&&(modbus.Hum_SensorValue[i] == 0xffff))
		{
				modbus.Hum_SensorValue[i] = 0 ;
				modbus.Hum_MeterValue[i] = 0;
				flash_change = 1 ;		
		}
	}
	flash_read(FlashDevice_ptr, EEP_FAC_CO2_TABLE_POINTS, &modbus.co2_fac_point, 2);
	if(modbus.co2_fac_point > 10) 
	{
			modbus.co2_fac_point = 0 ;
			flash_change = 1 ;
	}
	flash_read(FlashDevice_ptr, EEP_CUS_CO2_TABLE_POINTS, &modbus.co2_cus_point, 2);
	if(modbus.co2_cus_point > 10) 
	{
			modbus.co2_cus_point = 0 ;
			flash_change = 1 ;
	}
	
	flash_read(FlashDevice_ptr, EEP_HUM_POINT, &modbus.Hum_Cal_point, 2);
	if(modbus.Hum_Cal_point > 10) 
	{
			modbus.Hum_Cal_point = 0 ;
			flash_change = 1 ;
	}
	
	/************************offset***********************************/
	
	flash_read(FlashDevice_ptr, EEP_CO2_OFFSET, &modbus.co2_offset, 2);
	if(modbus.co2_offset == 0XFFFF) 
	{
			modbus.co2_offset = 500 ;
			flash_change = 1 ;
	}
	flash_read(FlashDevice_ptr, EEP_HUM_OFFSET, &modbus.HH_offset, 2);
	if(modbus.HH_offset == 0XFFFF) 
	{
			modbus.HH_offset = 500 ;
			flash_change = 1 ;
	}
	
	flash_read(FlashDevice_ptr, EEP_AQ_OFFSET, &modbus.Aq_offset, 2);
	if(modbus.Aq_offset == 0XFFFF) 
	{
			modbus.Aq_offset = 500 ;
			flash_change = 1 ;
	}
	
	flash_read(FlashDevice_ptr, EEP_PM25_OFFSET, &modbus.PM25_offset, 2);
	if(modbus.PM25_offset == 0XFFFF) 
	{
			modbus.PM25_offset = 500 ;
			flash_change = 1 ;
	}
	
	flash_read(FlashDevice_ptr, EEP_HT_OFFSET, &modbus.HT_offset, 2);
	if(modbus.HT_offset == 0XFFFF) 
	{
			modbus.HT_offset = 500 ;
			flash_change = 1 ;
	}
	
	flash_read(FlashDevice_ptr, EEP_PT_OFFSET, &modbus.PT_offset, 2);
	if(modbus.PT_offset == 0XFFFF) 
	{
			modbus.PT_offset = 500 ;
			flash_change = 1 ;
	}
	
	flash_read(FlashDevice_ptr, EEP_RTD_POINT, &modbus.Rtd_Point, 2);
	if(modbus.Rtd_Point == 0XFFFF) 
	{
			modbus.Rtd_Point = 0 ;
			flash_change = 1 ;
	}
	
	
	flash_read(FlashDevice_ptr, EEP_RTD_T0, &modbus.Rtd_Cal_T[0], 2);
	if(modbus.Rtd_Cal_T[0] == 0XFFFF) 
	{
			modbus.Rtd_Cal_T[0] = 0 ;
			flash_change = 1 ;
	}
	
	flash_read(FlashDevice_ptr, EEP_RTD_AD0, &modbus.Rtd_Cal_Ad[0], 2);
	if(modbus.Rtd_Cal_Ad[0] == 0XFFFF) 
	{
			modbus.Rtd_Cal_Ad[0] = 0 ;
			flash_change = 1 ;
	}
	flash_read(FlashDevice_ptr, EEP_RTD_T1, &modbus.Rtd_Cal_T[1], 2);
	if(modbus.Rtd_Cal_T[1] == 0XFFFF) 
	{
			modbus.Rtd_Cal_T[1] = 0 ;
			flash_change = 1 ;
	}
	
	flash_read(FlashDevice_ptr, EEP_RTD_AD1, &modbus.Rtd_Cal_Ad[1], 2);
	if(modbus.Rtd_Cal_Ad[1] == 0XFFFF) 
	{
			modbus.Rtd_Cal_Ad[1]  = 0 ;
			flash_change = 1 ;
	}
	
	flash_read(FlashDevice_ptr, EEP_RTD_REF, &modbus.Rtd_Ref, 2);
	if(modbus.Rtd_Ref == 0XFFFF) 
	{
			modbus.Rtd_Ref  = 0 ;
			flash_change = 1 ;
	}
	
	flash_read(FlashDevice_ptr, EEP_CO2_FILTER, &modbus.filter, 2);
	if(modbus.filter == 0XFFFF) 
	{
			modbus.filter  = 20 ;
			flash_change = 1 ;
	}
	
	flash_read(FlashDevice_ptr, EEP_FAC_CUS_TABLE, &modbus.co2_fac_cus_table, 2);
	if(modbus.co2_fac_cus_table == 0XFFFF) 
	{
			modbus.co2_fac_cus_table  = 0 ;
			flash_change = 1 ;
	}
	
	
	flash_read(FlashDevice_ptr, EEP_BACKGROUND_PPM, &modbus.background_ppm, 2);
	if(modbus.background_ppm == 0XFFFF) 
	{
			modbus.background_ppm  = 400 ;
			flash_change = 1 ;
	}
	flash_read(FlashDevice_ptr, EEP_MAX_ADJUST_PER_DAY, &modbus.background_max_adj, 2);
	if(modbus.background_max_adj == 0XFFFF) 
	{
			modbus.background_max_adj  = 1 ;
			flash_change = 1 ;
	}
	
	flash_read(FlashDevice_ptr, EEP_BACKGROUND_DAYS, &modbus.backgroud_days, 2);
	if(modbus.backgroud_days == 0XFFFF) 
	{
			modbus.backgroud_days  = 14 ;
			flash_change = 1 ;
	}
	
	
	flash_read(FlashDevice_ptr, EEP_BACKGROUND_TIME, &modbus.backgroud_time, 2);
	if(modbus.backgroud_time == 0XFFFF) 
	{
			modbus.backgroud_time  = 1 ;
			flash_change = 1 ;
	}
	
	flash_read(FlashDevice_ptr, EEP_AUTO_CAL_ON_OFF, &modbus.auto_cal_on_off, 2);
	if(modbus.auto_cal_on_off == 0XFFFF) 
	{
			modbus.auto_cal_on_off  = 0 ;
			flash_change = 1 ;
	}
	
	flash_read(FlashDevice_ptr, EEP_BACKGROUND_OFFSET, &read_temp, 2);
	if(read_temp == 0XFFFF) 
	{
			read_temp = 0 ;
			flash_change = 1 ;
	}
	modbus.backgroud_offset = (int16_t)read_temp ;
	
}

void write_to_flash(void)
{
	uint8_t i ;
	uint16_t status ;
	uint8_t str[20];
	uint16_t write_temp ;
	if(flash_change == 1)
	{
		status = flash_erase(FlashDevice_ptr, EEP_BASE_ADDRESS, 1UL); 
		if(status)
		{
			sprintf((char*)str, "status =%u\n\r", status);
			AS2_SendBlock(AS2_ptr, str, strlen((char*)str))  ;
			Delay(5) ;
		}
//		AS2_SendBlock(AS2_ptr, "flashwrite\n\r", strlen("flashwrite\n\r"))  ;
//		Delay(5) ;
		for(i=0; i<10; i++)
			{
					flash_write(FlashDevice_ptr, &modbus.co2_fac_ad[i], EEP_FAC_CO2_CAL_AD1+4*i, 2) ;
					flash_write(FlashDevice_ptr, &modbus.co2_fac_ppm[i], EEP_FAC_CO2_CAL_PPM1+4*i, 2) ;
				
					flash_write(FlashDevice_ptr, &modbus.co2_cus_ad[i], EEP_CUS_CO2_CAL_AD1+4*i, 2) ;
					flash_write(FlashDevice_ptr, &modbus.co2_cus_ppm[i], EEP_CUS_CO2_CAL_PPM1+4*i, 2) ;
					flash_write(FlashDevice_ptr, &modbus.Hum_MeterValue[i], EEP_HUM_METER0+4*i, 2) ;
				  flash_write(FlashDevice_ptr, &modbus.Hum_SensorValue[i], EEP_HUM_SENSOR0+4*i, 2) ;
			}
			flash_write(FlashDevice_ptr, &modbus.Hum_Cal_point, EEP_HUM_POINT, 2) ;
			flash_write(FlashDevice_ptr, &modbus.co2_fac_point, EEP_FAC_CO2_TABLE_POINTS, 2) ;
			flash_write(FlashDevice_ptr, &modbus.co2_cus_point, EEP_CUS_CO2_TABLE_POINTS, 2) ;
			
			flash_write(FlashDevice_ptr, &modbus.co2_offset, EEP_CO2_OFFSET, 2) ;
			flash_write(FlashDevice_ptr, &modbus.HH_offset, EEP_HUM_OFFSET, 2) ;
			flash_write(FlashDevice_ptr, &modbus.Aq_offset, EEP_AQ_OFFSET, 2) ;
			flash_write(FlashDevice_ptr, &modbus.PM25_offset, EEP_PM25_OFFSET, 2) ;
			flash_write(FlashDevice_ptr, &modbus.HT_offset, EEP_HT_OFFSET, 2) ;
			flash_write(FlashDevice_ptr, &modbus.PT_offset, EEP_PT_OFFSET, 2) ;
			
			flash_write(FlashDevice_ptr, &modbus.Rtd_Point, EEP_RTD_POINT, 2) ;
			flash_write(FlashDevice_ptr, &modbus.Rtd_Cal_T[0], EEP_RTD_T0, 2) ;
			flash_write(FlashDevice_ptr, &modbus.Rtd_Cal_Ad[0], EEP_RTD_AD0, 2) ;
			flash_write(FlashDevice_ptr, &modbus.Rtd_Cal_T[1], EEP_RTD_T1, 2) ;
			flash_write(FlashDevice_ptr, &modbus.Rtd_Cal_Ad[1], EEP_RTD_AD1, 2) ;
			flash_write(FlashDevice_ptr, &modbus.Rtd_Ref, EEP_RTD_REF, 2) ;
			flash_write(FlashDevice_ptr, &modbus.co2_fac_cus_table, EEP_FAC_CUS_TABLE, 2) ;
			
			flash_write(FlashDevice_ptr, &modbus.background_ppm, 			EEP_BACKGROUND_PPM, 2) ;
			flash_write(FlashDevice_ptr, &modbus.background_max_adj, 	EEP_MAX_ADJUST_PER_DAY, 2) ;
			flash_write(FlashDevice_ptr, &modbus.backgroud_days, 			EEP_BACKGROUND_DAYS, 2) ;
			flash_write(FlashDevice_ptr, &modbus.backgroud_time, 			EEP_BACKGROUND_TIME, 2) ;
			flash_write(FlashDevice_ptr, &modbus.auto_cal_on_off, 		EEP_AUTO_CAL_ON_OFF, 2) ;
			
			write_temp = (uint16_t)modbus.backgroud_offset ;
			flash_write(FlashDevice_ptr, &write_temp, EEP_BACKGROUND_OFFSET, 2) ;
			
			
			flash_change = 0 ;
	}	
}










