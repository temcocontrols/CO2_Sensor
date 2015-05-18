#include <stdio.h>
#include <string.h>
#include "modbus.h"
#include "registerlist.h"

#include "crc.h"
#include "extern.h"
#include "flash.h"

STR_MODBUS modbus ;

uint8_t USART_RX_BUF[USART_REV_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
uint8_t uart_send[USART_SEND_LEN] ;
uint8_t transmit_finished = 0 ; 
uint8_t revce_count = 0 ;

uint8_t serial_receive_timeout_count ;
uint8_t dealwithTag ;
STR_MODBUS modbus ;
uint8_t DealwithTag ;
uint16_t sendbyte_num = 0 ;
uint16_t Test_Flag[10] ;





void serial_restart(void)
{
//	TXEN_RECEIVE();
	revce_count = 0;
	dealwithTag = 0;
} 

//it is ready to send data by serial port . 
static void initSend_COM(void)
{
	//TXEN_SEND();
}

//void send_byte(u8 ch, u8 crc)
//{	
//	USART_ClearFlag(USART1, USART_FLAG_TC); 
//	USART_SendData(USART1,  ch);
//	if(crc)
//	{
//		crc16_byte(ch);
//	}
//}
//void USART_SendDataString(u8 *pbuf, u8 num)
// {
//     sendbyte_num = num ;
//	 uart_num = 0 ;
//	 pDataByte = pbuf ;
//	 USART_ClearFlag(USART1, USART_FLAG_TC);   
//     USART_SendData(USART1, pDataByte[uart_num++] ); 
//	 tx_count = 20 ;
// }
 void USART_SendDataString( uint8_t num )
 {
		 AS1_SendBlock(AS1_ptr, uart_send, num) ;
 }
void modbus_init(void)
{

	//serial_restart();
	serial_receive_timeout_count = SERIAL_RECEIVE_TIMEOUT;
	modbus.address = 254;		

}

//void internalDeal(uint8_t start_address)
//{

//	//uint8_t address_temp ;

//	if(USART_RX_BUF[1] == WRITE_VARIABLES)
//	{
//			if(start_address == MODBUS_UPDATE_STATUS )
//			{  
//				 modbus.update = USART_RX_BUF[5]; 
//				if(modbus.update == 0x7f)	
//				{
//				}
//							
//			}
//				
//	}
//}

// when had received data ,the routine begin to dealwith interal by command external.
static void internalDeal(uint16_t start_address)
{
	uint8_t  address_temp1,  address_temp2;
	uint16_t modbus_out ;
	
	if(USART_RX_BUF[1] == WRITE_VARIABLES)
	{
//		if((start_address >= MODBUS_SERIALNUMBER_LOWORD) && (start_address <= (MODBUS_SERIALNUMBER_LOWORD + 3)))
//		{
//			if((start_address == MODBUS_SERIALNUMBER_LOWORD))
//			{
//				modbus.serial_Num[0] = USART_RX_BUF[5];
//				modbus.serial_Num[1] = USART_RX_BUF[4];
////				flash_write_int(EEP_SERIALNUMBER_LOWORD, USART_RX_BUF[5], FLASH_MEMORY);
////				flash_write_int(EEP_SERIALNUMBER_LOWORD+1, USART_RX_BUF[4], FLASH_MEMORY);
//				modbus.SNWriteflag |= 0x01;
//				if(modbus.SNWriteflag & 0x02)
//					modbus.update = 0;
//			}
//			else if((start_address == MODBUS_SERIALNUMBER_HIWORD))
//			{
//				modbus.serial_Num[2] = USART_RX_BUF[5];
//				modbus.serial_Num[3] = USART_RX_BUF[4];
////			    flash_write_int(EEP_SERIALNUMBER_HIWORD, data_buffer[5], FLASH_MEMORY);
////				flash_write_int(EEP_SERIALNUMBER_HIWORD+1, data_buffer[4], FLASH_MEMORY);
//				modbus.SNWriteflag |= 0x02;
//				if(modbus.SNWriteflag & 0x01)
//					modbus.update = 0;
//			}
//		}
//		else 
if(start_address == MODBUS_ADDRESS)
		{
			modbus.address = USART_RX_BUF[5];  
			//iap_program_data_byte(0, DATA_TO_FIRMWARE + MODBUS_ADDRESS);	// it will reset the address to 254 if in ISP mode
			//flash_write_int(EEP_ADDRESS, modbus.address, FLASH_MEMORY);
		}
		else if(start_address == MODBUS_PRODUCT_MODEL)
		{
			modbus.product = USART_RX_BUF[5];
//			flash_write_int(EEP_PRODUCT_MODEL, modbus.product, FLASH_MEMORY);
			modbus.SNWriteflag |= 0x08;
//			flash_write_int(EEP_SERIALNUMBER_WRITE_FLAG, SNWriteflag, FLASH_MEMORY);
		}
//		else if(start_address == MODBUS_UPDATE_STATUS)
//		{
////			update_flash = data_buffer[5];
////			if(update_flash == 0x9F)
////			{
////				//...
////			}		
////			else if((update_flash == 0x8E) || (update_flash == 0x8F))
////			{
////				if(update_flash == 0x8e)
////				{
////					SNWriteflag = 0x00;

////					modbus.serialNum[0] = 0;
////					modbus.serialNum[1] = 0;
////					modbus.serialNum[2] = 0;
////					modbus.serialNum[3] = 0;
////				}
////			}
//		}
//		else if(start_address == MODBUS_BAUDRATE)
//		{
//			if(data_buffer[5] == 1)
//			{
//				baudrate = 1;
//				PCON |= 0x80;
//				SERIAL_RECEIVE_TIMEOUT = 3;
//			}
//			else if(data_buffer[5] == 0)
//			{
//				baudrate = 0;
//		 		PCON &= ~0x80;
//				SERIAL_RECEIVE_TIMEOUT = 7;
//			}
//		}
//		else if(start_address == MODBUS_COMPENSATION_ON_OFF)
//		{
//			if(data_buffer[5] > 1) data_buffer[5] = 1 ;
//			modbus.Compensation_On_Off = data_buffer[5];
//			flash_write_int(EEP_CO2_COMPENSATION_ON_OFF, modbus.Compensation_On_Off, FLASH_MEMORY);	
//		}

		else if(start_address == MODBUS_FILTER)
		{
				modbus.filter =  (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
				flash_change = 1  ;
		}
		else if(start_address == MODBUS_HT )
		{
			modbus_out =  (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
			modbus.HT_offset = modbus_out + 500- modbus.HT ;
				flash_change = 1  ;
		}
		else if(start_address ==  MODBUS_HUM )
		{
			modbus_out =  (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
			modbus.HH_offset = modbus_out + 500- modbus.HH ;
			flash_change = 1  ;
		}
		else if(start_address ==  MODBUS_PM25 )
		{
			modbus_out =  (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
			modbus.PM25_offset = modbus_out + 500- modbus.PM25 ;
			flash_change = 1  ;
		}
		else if(start_address ==  MODBUS_AQ )
		{
			modbus_out =  (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
			modbus.Aq_offset = modbus_out + 500- modbus.Aq ;
			flash_change = 1  ;
		}
		else if(start_address ==  MODBUS_PT )
		{
			modbus_out =  (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
			modbus.PT_offset = modbus_out + 500- modbus.PT ;
			flash_change = 1  ;
		}
		else if(start_address == MODBUS_FAC_CUS_TABLE)
		{
				modbus.co2_fac_cus_table =  (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
				if(modbus.co2_fac_cus_table > 1) modbus.co2_fac_cus_table = 1 ;
				flash_change = 1  ;
		}
		/*Calibrate Co2*/
		else if(start_address == MODDBUS_FAC_CAL_POINT)
		{
				modbus.co2_fac_point =  (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
				flash_change = 1  ;
		}
		else if((start_address >= MODBUS_FAC_PPM0)&&(start_address<= MODBUS_FAC_AD9))
		{
				
			  address_temp1 = (start_address - MODBUS_FAC_PPM0)/2 ;
			  address_temp2 = (start_address - MODBUS_FAC_PPM0)%2 ;
				if(address_temp2 == 0)
				{
					modbus.co2_fac_ppm[address_temp1]	= (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
				}
				else
				{
					modbus.co2_fac_ad[address_temp1] =  (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
				}
				flash_change = 1  ;
		}
		
		else if(start_address == MODBUS_BACKGROUND_PPM)
		{
		modbus.background_ppm =  (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
		flash_change = 1  ;
		}
		else if(start_address == MODBUS_MAX_ADJUST_PER_DAY)
		{
		modbus.background_max_adj =  (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
		flash_change = 1  ;
		}
		else if(start_address == MODBUS_BACKGROUND_DAYS)
		{
		modbus.backgroud_days =  (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
		flash_change = 1  ;
		}
		else if(start_address == MODBUS_BACKGROUND_TIME)
		{
			modbus.backgroud_time =  (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
			flash_change = 1  ;
		}
		else if(start_address == MODBUS_AUTO_CAL_ON_OFF)
		{
			modbus.auto_cal_on_off =  (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
			flash_change = 1  ;
		}
		else if(start_address == MODBUS_BACKGROUND_OFFSET)
		{
			modbus.backgroud_offset =  (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
			flash_change = 1  ;
		}
		
		
		else if(start_address == MODBUS_RTD_POINT)
		{
				modbus.Rtd_Point =  (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
				flash_change = 1  ;
		}
		else if(start_address == MODBUS_CAL_RTD_T0)
		{
				modbus.Rtd_Cal_T[0] =  (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
				flash_change = 1  ;
		}
		else if(start_address == MODBUS_CAL_RTD_AD0)
		{
				modbus.Rtd_Cal_Ad[0] =  (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
				flash_change = 1  ;
		}
		else if(start_address == MODBUS_CAL_RTD_T1)
		{
				modbus.Rtd_Cal_T[1] =  (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
				flash_change = 1  ;
		}
		else if(start_address == MODBUS_CAL_RTD_AD1)
		{
				modbus.Rtd_Cal_Ad[1] =  (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
				flash_change = 1  ;
		}
		else if(start_address == MODBUS_CO2_OFFSET)
		{
				modbus.co2_offset =  (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
				flash_change = 1  ;
		}
		else if(start_address == MODBUS_PM25_OFFSET)
		{
				modbus.PM25_offset =  (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
				flash_change = 1  ;
		}
		
		else if(start_address == MODBUS_HUM_POINT)
		{
				modbus.Hum_Cal_point =  (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
				flash_change = 1  ;
		}
		else if((start_address >= MODBUS_METER_HUM0)&&(start_address<= MODBUS_SENSOR_HUM9))
		{
				
			  address_temp1 = (start_address - MODBUS_METER_HUM0)/2 ;
			  address_temp2 = (start_address - MODBUS_METER_HUM0)%2 ;
				if(address_temp2 == 0)
				{
					modbus.Hum_MeterValue[address_temp1]	= (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
//						modbus.Hum_MeterValue[address_temp1] = 44 ;
				}
				else
				{
					modbus.Hum_SensorValue[address_temp1] =  (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
//						modbus.Hum_SensorValue[address_temp1] = 33 ;
				}
				flash_change = 1  ;
		}
		else if(start_address == MODBUS_RTD_REF)
		{
				modbus.Rtd_Ref =  (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
				flash_change = 1  ;
		}
		else if((start_address >= MODBUS_CUS_PPM0)&&(start_address<= MODBUS_CUS_AD9))
		{
				
			  address_temp1 = (start_address - MODBUS_CUS_PPM0)/2 ;
			  address_temp2 = (start_address - MODBUS_CUS_PPM0)%2 ;
				if(address_temp2 == 0)
				{
					modbus.co2_cus_ppm[address_temp1]	= (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
				}
				else
				{
					modbus.co2_cus_ad[address_temp1] =  (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] ;
				}
				flash_change = 1  ;
		}
		
//		else if(start_address == MODBUS_RTD_POINT)
//		{
//				modbus.Rtd_Cal_Point = data_buffer[5] ;
//			  flash_write_int(EEP_RTD_POINT, modbus.Rtd_Cal_T[0], FLASH_MEMORY);
//		}
//		/*Calibrate Rtd */
//		else if(start_address == MODBUS_CAL_RTD_T0)
//		{
//				modbus.Rtd_Cal_T[0] = (data_buffer[4]<<8) + data_buffer[5] ;
//				modbus.Rtd_Cal_Ad[0] = AD.Rtd ;
//				flash_write_int(EEP_RTD_T0, modbus.Rtd_Cal_T[0], FLASH_MEMORY);
//				flash_write_int(EEP_RTD_AD0, modbus.Rtd_Cal_Ad[0], FLASH_MEMORY);
//		}
//		else if(start_address == MODBUS_CAL_RTD_T1)
//		{
//				modbus.Rtd_Cal_T[1] = (data_buffer[4]<<8) + data_buffer[5] ;
//				modbus.Rtd_Cal_Ad[1] = AD.Rtd ;
//				flash_write_int(EEP_RTD_T1, modbus.Rtd_Cal_T[1], FLASH_MEMORY);
//				flash_write_int(EEP_RTD_AD1, modbus.Rtd_Cal_Ad[1], FLASH_MEMORY);
//		}
//		/*Calibrate humidity */
//		else if(start_address == MODBUS_HUM_POINT)
//		{
//				modbus.Hum_Cal_point = data_buffer[5] ;
//			  flash_write_int(EEP_HUM_CAL_POINTS, modbus.Hum_Cal_point, FLASH_MEMORY);
//		}
//		else if((start_address >= MODBUS_METER_HUM0)&&(start_address <= MODBUS_READ_HUM9))
//		{
//				temp = (start_address - MODBUS_METER_HUM0)/2 ;
//				modbus.Hum_Real_Value[temp] = (data_buffer[4]<<8) + data_buffer[5] ;
//				flash_write_int(EEP_HUM_METER_VALUE0+2*temp, modbus.Hum_Real_Value[temp], FLASH_MEMORY);
//				flash_write_int(EEP_HUM_READ_VALUE0+2*temp,  modbus.Hum_Read_Value[temp], FLASH_MEMORY);
//		}
//		else if(start_address == MODBUS_START_STOP_DETECT)
//		{
//			Co2_Detect_flag = data_buffer[5] ;
//			if(Co2_Detect_flag == 1)
//			{
//				start_detect_roution();
//			}
//			else if(Co2_Detect_flag == 0)
//			{
//					stop_detect_roution();
//			}
//		}
	}//END OF WRITE_VARIABLES
	else if(USART_RX_BUF[1] == READ_VARIABLES)
	{
		//clear the isp state flag
	}


}
    


static void responseData(uint16_t start_address)
{
	uint8_t num, i, temp1, temp2;
	uint16_t send_cout = 0 ;
	uint16_t address_temp ;
	uint8_t   buffer1, buffer2 ;
	uint16_t modbus_out ;
	if(USART_RX_BUF[1] == WRITE_VARIABLES)
	{
		for(i = 0; i < rece_size; i++)
		{
			uart_send[send_cout++] = USART_RX_BUF[i] ;
		}
		USART_SendDataString(send_cout);
	}
	else if(USART_RX_BUF[1] == MULTIPLE_WRITE)
	{
		for(i = 0; i < 6; i++)
		{
			 uart_send[send_cout++] = USART_RX_BUF[i] ;
			crc16_byte(USART_RX_BUF[i]);
		}
		uart_send[send_cout++] = CRChi ;
		uart_send[send_cout++] = CRClo ;
		USART_SendDataString(send_cout);		
	}
	else if(USART_RX_BUF[1] == READ_VARIABLES)
	{
		uint16_t address;
		//uint16_t address_temp ;
		num = USART_RX_BUF[5];		
		uart_send[send_cout++] = USART_RX_BUF[0] ;
		uart_send[send_cout++] = USART_RX_BUF[1] ;
		uart_send[send_cout++] = (USART_RX_BUF[5]<<1) ;
		crc16_byte(USART_RX_BUF[0]);
		crc16_byte(USART_RX_BUF[1]);
		crc16_byte((USART_RX_BUF[5]<<1));
		for(i = 0; i < num; i++)
		{
			address = start_address + i;
			if(address <= MODBUS_SERIALNUMBER_HIWORD + 1)
			{
				temp1 = 0 ;
				temp2 = modbus.serial_Num[address] ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_VERSION_NUMBER_LO)
			{
				temp1 = 0 ;
				//temp2 =  (uint8_t)(SW_VER) ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);		
			}
			else if(address == MODBUS_VERSION_NUMBER_HI)
			{
				temp1 = 0 ;
			//	temp2 =  (uint8_t)(SW_VER >> 8) ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);	
			}
			else if(address == MODBUS_ADDRESS)
			{
				temp1 = 0 ;
				temp2 =  modbus.address;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);		
			}
			else if(address == MODBUS_PRODUCT_MODEL)
			{
				temp1 = 0 ;
				//temp2 =  PRODUCT_ID;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_HARDWARE_REV)
			{
				temp1 = 0 ;
				//temp2 =  HW_VER;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);				
			}
			else if(address == MODBUS_BAUDRATE)
			{
				temp1 = 0 ;
				temp2 =  modbus.baud;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);				
			}
			
//			else if(address == MODBUS_BASE_ADDRESS)
//			{
//				temp1 = 0 ;
//				temp2 =  0;
//				uart_send[send_cout++] = temp1 ;
//				uart_send[send_cout++] = temp2 ;
//				crc16_byte(temp1);
//				crc16_byte(temp2);
//			}
			else if(address == MODBUS_UPDATE_STATUS)
			{
				temp1 = 0 ;
				temp2 =   modbus.update;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_SERINALNUMBER_WRITE_FLAG)
			{
				temp1 = 0 ;
				temp2 =  modbus.SNWriteflag ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			
			else if(address == MODBUS_CO2_AD)
			{
				temp1 = modbus.Co2_Ad>>8;
				temp2 =  modbus.Co2_Ad ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
				modbus.st_dectt = 1 ;
			}
			else if(address == MODBUS_RTD_AD)
			{
				temp1 = modbus.Rtd_Ad>>8;
				temp2 =  modbus.Rtd_Ad ;
				
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_AQ_AD)
			{
				temp1 = modbus.Aq_Ad>>8;
				temp2 =  modbus.Aq_Ad ;
				
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_PM25_AD)
			{
				temp1 = modbus.Pm25_Ad>>8;
				temp2 =  modbus.Pm25_Ad ;
				
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_COMPENSATION_ON_OFF)
			{
				temp1 = 0;
				temp2 =  modbus.Compensation_On_Off ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_RTD)
			{
				temp1 = modbus.Rtd>>8;
				temp2 =  modbus.Rtd ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_RTD_AD)
			{
				temp1 = modbus.Rtd_Ad>>8;
				temp2 =  modbus.Rtd_Ad ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_FILTER)
			{
				temp1 = modbus.filter>>8;
				temp2 =  modbus.filter ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_HT)
			{
				
				modbus_out = modbus.HT + 500 - modbus.HT_offset ;
				temp1 = modbus_out >> 8;
				temp2 = modbus_out ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_CO2_PPM)
			{
				modbus_out = modbus.Co2 + 500 - modbus.co2_offset ;				
				temp1 = modbus_out>>8;
				temp2 = modbus_out;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_PM25)
			{
				modbus_out = modbus.PM25 + 500 - modbus.PM25_offset ;
				temp1 = modbus_out >>8;
				temp2 = modbus_out ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_HUM)
			{
				modbus_out = modbus.HH + 500 - modbus.HH_offset ;
				temp1 = modbus_out >>8;
				temp2 =  modbus_out ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_AQ)
			{
				modbus_out = modbus.Aq + 500 - modbus.Aq_offset ;
				temp1 = modbus_out>>8;
				temp2 =  modbus_out;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_PRESURE_HI)
			{
				temp1 = (modbus.PP>>24)&0xff;
				temp2 =  (modbus.PP>>16)&0xff;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_PRESURE_LO)
			{
				temp1 = (modbus.PP>>8)&0xff;
				temp2 =  (modbus.PP)&0xff;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_PT)
			{
				modbus_out = modbus.PT + 500 - modbus.PT_offset ;
				temp1 = (modbus_out>>8)&0xff;
				temp2 =  modbus_out;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_FAC_CUS_TABLE)
			{
				temp1 = (modbus.co2_fac_cus_table>>8)&0xff;
				temp2 =  modbus.co2_fac_cus_table;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			
			else if(address == MODDBUS_FAC_CAL_POINT)
			{
				temp1 = (modbus.co2_fac_point>>8)&0xff;
				temp2 =  modbus.co2_fac_point ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if((address >= MODBUS_FAC_PPM0)&&(address <= MODBUS_FAC_AD9))
			{
					address_temp = address - MODBUS_FAC_PPM0 ;
				  buffer1 = address_temp%2 ;
				  buffer2 = address_temp/2 ;
					if(buffer1 == 0)
					{
							temp1 =  modbus.co2_fac_ppm[buffer2]>>8 ;
							temp2 =  modbus.co2_fac_ppm[buffer2] ;
					}
					else
					{
							temp1 =  modbus.co2_fac_ad[buffer2]>>8 ;
							temp2 =  modbus.co2_fac_ad[buffer2] ;
					}
					uart_send[send_cout++] = temp1 ;
					uart_send[send_cout++] = temp2 ;
					crc16_byte(temp1);
					crc16_byte(temp2);
					
			}
			else if(address == MODBUS_BACKGROUND_PPM)
			{
				temp1 = (modbus.background_ppm>>8)&0xff;
				temp2 =  modbus.background_ppm ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_MAX_ADJUST_PER_DAY)
			{
				temp1 = (modbus.background_max_adj>>8)&0xff;
				temp2 =  modbus.background_max_adj ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_BACKGROUND_DAYS)
			{
				temp1 = (modbus.backgroud_days>>8)&0xff;
				temp2 =  modbus.backgroud_days ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
						else if(address == MODBUS_BACKGROUND_TIME)
			{
				temp1 = (modbus.backgroud_time>>8)&0xff;
				temp2 =  modbus.backgroud_time ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_AUTO_CAL_ON_OFF)
			{
				temp1 = (modbus.auto_cal_on_off>>8)&0xff;
				temp2 =  modbus.auto_cal_on_off ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_BACKGROUND_OFFSET)
			{
				temp1 = (modbus.backgroud_offset>>8)&0xff;
				temp2 =  modbus.backgroud_offset ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			
			
			
			else if(address == MODBUS_RTD_POINT)
			{
				temp1 = (modbus.Rtd_Point>>8)&0xff;
				temp2 =  modbus.Rtd_Point ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_CAL_RTD_AD0)
			{
				temp1 = (modbus.Rtd_Cal_Ad[0]>>8)&0xff;
				temp2 =  modbus.Rtd_Cal_Ad[0] ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_CAL_RTD_T0)
			{
				temp1 = (modbus.Rtd_Cal_T[0]>>8)&0xff;
				temp2 =  modbus.Rtd_Cal_T[0] ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}			
			else if(address == MODBUS_CAL_RTD_T1)
			{
				temp1 = (modbus.Rtd_Cal_T[1]>>8)&0xff;
				temp2 =  modbus.Rtd_Cal_T[1] ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_CAL_RTD_AD1)
			{
				temp1 = (modbus.Rtd_Cal_Ad[1]>>8)&0xff;
				temp2 =  modbus.Rtd_Cal_Ad[1] ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_CO2_OFFSET)
			{
				temp1 = (modbus.co2_offset>>8)&0xff;
				temp2 =  modbus.co2_offset ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}

			else if(address == MODBUS_PM25_OFFSET)
			{
				temp1 = (modbus.PM25_offset>>8)&0xff;
				temp2 =  modbus.PM25_offset ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_AQ_OFFSET)
			{
				temp1 = (modbus.Aq_offset>>8)&0xff;
				temp2 =  modbus.Aq_offset ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_HT_OFFSET)
			{
				temp1 = (modbus.HT_offset>>8)&0xff;
				temp2 =  modbus.HT_offset ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_PT_OFFSET)
			{
				temp1 = (modbus.PT_offset>>8)&0xff;
				temp2 =  modbus.PT_offset ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_HUM_POINT)
			{
				temp1 = (modbus.Hum_Cal_point>>8)&0xff;
				temp2 =  modbus.Hum_Cal_point ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if((address >= MODBUS_METER_HUM0)&&(address <= MODBUS_SENSOR_HUM9))
			{
					address_temp = address - MODBUS_METER_HUM0 ;
				  buffer1 = address_temp%2 ;
				  buffer2 = address_temp/2 ;
					if(buffer1 == 0)
					{
							temp1 =  modbus.Hum_MeterValue[buffer2]>>8 ;
							temp2 =  modbus.Hum_MeterValue[buffer2] ;
					}
					else
					{
							temp1 =  modbus.Hum_SensorValue[buffer2]>>8 ;
							temp2 =  modbus.Hum_SensorValue[buffer2] ;
					}
					uart_send[send_cout++] = temp1 ;
					uart_send[send_cout++] = temp2 ;
					crc16_byte(temp1);
					crc16_byte(temp2);					
			}
			else if(address == MODBUS_RTD_REF)
			{
				temp1 = (modbus.Rtd_Ref>>8)&0xff;
				temp2 =  modbus.Rtd_Ref ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_START_STOP_DETECT)
			{
				temp1 = (modbus.st_dectt>>8)&0xff;
				temp2 =  modbus.st_dectt ;
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if((address >= MODBUS_CUS_PPM0)&&(address <= MODBUS_CUS_AD9))
			{
					address_temp = address - MODBUS_CUS_PPM0 ;
				  buffer1 = address_temp%2 ;
				  buffer2 = address_temp/2 ;
					if(buffer1 == 0)
					{
							temp1 =  modbus.co2_cus_ppm[buffer2]>>8 ;
							temp2 =  modbus.co2_cus_ppm[buffer2] ;
					}
					else
					{
							temp1 =  modbus.co2_cus_ad[buffer2]>>8 ;
							temp2 =  modbus.co2_cus_ad[buffer2] ;
					}
					uart_send[send_cout++] = temp1 ;
					uart_send[send_cout++] = temp2 ;
					crc16_byte(temp1);
					crc16_byte(temp2);					
			}
			
			
			
			
			else if(address == MODBUS_TEST1)
			{ 				
				temp1 = (Test_Flag[0]>>8)&0xff ;
				temp2 =  Test_Flag[0]&0xff; 
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_TEST2)
			{ 				
				temp1 = (Test_Flag[1]>>8)&0xff ;
				temp2 =  Test_Flag[1]&0xff;  
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_TEST3)
			{ 				
				temp1 = (Test_Flag[2]>>8)&0xff ;
				temp2 =  Test_Flag[2]&0xff; 
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_TEST4)
			{ 				
				temp1 = (Test_Flag[3]>>8)&0xff ;
				temp2 =  Test_Flag[3]&0xff; 
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_TEST5)
			{ 				
				temp1 = (Test_Flag[4]>>8)&0xff ;
				temp2 =  Test_Flag[4]&0xff; 
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_TEST6)
			{ 				
				temp1 = (Test_Flag[5]>>8)&0xff ;
				temp2 =  Test_Flag[5]&0xff; 
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_TEST7)
			{ 				
				temp1 = (Test_Flag[6]>>8)&0xff ;
				temp2 =  Test_Flag[6]&0xff;  
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_TEST8)
			{ 				
				temp1 = (Test_Flag[7]>>8)&0xff ;
				temp2 =  Test_Flag[7]&0xff;  
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_TEST9)
			{ 				
				temp1 = (Test_Flag[8]>>8)&0xff ;
				temp2 =  Test_Flag[8]&0xff;  
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_TEST10)
			{ 				
				temp1 = (Test_Flag[9]>>8)&0xff ;
				temp2 =  Test_Flag[9]&0xff;   
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_TEST11)
			{ 				
				temp1 = 0 ;
			//	temp2 = switch_state_buf[8]; 
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_TEST12)
			{ 				
				temp1 = 0 ;
			//	temp2 = switch_state_buf[9]; 
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_TEST13)
			{ 				
				temp1 = 0 ;
			//	temp2 = switch_state_buf[10]; 
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_TEST14)
			{ 				
				temp1 = 0 ;
			//	temp2 = switch_state_buf[11]; 
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else if(address == MODBUS_TEST15)
			{ 				
				temp1 = 0 ;
			//	temp2 = switch_state_buf[12]; 
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}
			else
			{
				temp1 = 0 ;
				temp2 =  1; 
				uart_send[send_cout++] = temp1 ;
				uart_send[send_cout++] = temp2 ;
				crc16_byte(temp1);
				crc16_byte(temp2);
			}

		}//end of number
		temp1 = CRChi ;
		temp2 =  CRClo; 
		uart_send[send_cout++] = temp1 ;
		uart_send[send_cout++] = temp2 ;
		USART_SendDataString(send_cout);
	}
	else if(USART_RX_BUF[1] == CHECKONLINE)
	{

	}
}
uint8_t checkData(uint16_t address)
{
	//static unsigned char xdata rand_read_ten_count = 0 ;
	uint16_t crc_val;
	//u8 minaddr,maxaddr, variable_delay;
	//u8 i;
	// check if packet completely received
	if(revce_count != rece_size)
		return 0;

	// check if talking to correct device ID
	if(USART_RX_BUF[0] != 255 && USART_RX_BUF[0] != modbus.address && USART_RX_BUF[0] != 0)
		return 0;	

	//  --- code to verify what is on the network ---------------------------------------------------
//	if( USART_RX_BUF[1] == CHECKONLINE)
//	{
//		crc_val = crc16(USART_RX_BUF,4) ;
//		if(crc_val != (USART_RX_BUF[4]<<8) + USART_RX_BUF[5] )
//		{
//			return FALSE;
//		}
//		minaddr = (USART_RX_BUF[2] >= USART_RX_BUF[3] ) ? USART_RX_BUF[3] : USART_RX_BUF[2] ;	
//		maxaddr = (USART_RX_BUF[2] >= USART_RX_BUF[3] ) ? USART_RX_BUF[2] : USART_RX_BUF[3] ;	
//		if(info[6] < minaddr || info[6] > maxaddr)
//			return FALSE;
//		else
//		{	// in the TRUE case, we add a random delay such that the Interface can pick up the packets
//			srand(heart_beat);
//			variable_delay = rand() % 20;
//			for ( i=0; i<variable_delay; i++)
//				delay_us(100);
//	
//			return TRUE;
//		}

	//}
	// ------------------------------------------------------------------------------------------------------



	// check that message is one of the following
	if( (USART_RX_BUF[1]!=READ_VARIABLES) && (USART_RX_BUF[1]!=WRITE_VARIABLES) && (USART_RX_BUF[1]!=MULTIPLE_WRITE) )
		return 0;
	// ------------------------------------------------------------------------------------------------------
		// ------------------------------------------------------------------------------------------------------
		
//	if(USART_RX_BUF[2]*256 + USART_RX_BUF[3] ==  FLASH_ADDRESS_PLUG_N_PLAY)
//	{
//		if(USART_RX_BUF[1] == WRITE_VARIABLES)
//		{
//			if(USART_RX_BUF[6] != info[0]) 
//			return FALSE;
//			if(USART_RX_BUF[7] != info[1]) 
//			return FALSE;
//			if(USART_RX_BUF[8] != info[2])  
//			return FALSE;
//			if(USART_RX_BUF[9] != info[3]) 
//			return FALSE;
//		}
//		if (data_buffer[1] == READ_VARIABLES)
//		{
//			randval = rand() % 10 / 2 ;
//		}
//		if(randval != RESPONSERANDVALUE)
//		{
////mhf:12-29-05 if more than 5 times does not response read register 10,reponse manuly.
//			rand_read_ten_count++;
//			if(rand_read_ten_count%5 == 0)
//			{
//				rand_read_ten_count = 0;
//				randval = RESPONSERANDVALUE;
//				variable_delay = rand() % 10;
//				for ( i=0; i<variable_delay; i++)
//					delay_us(75);
//			}
//			else
//				return FALSE;
//		}
//		else
//		{		
//			// in the TRUE case, we add a random delay such that the Interface can pick up the packets
//			rand_read_ten_count = 0;
//			variable_delay = rand() % 10;
//			for ( i=0; i<variable_delay; i++)
//				delay_us(75);				
//		}
//		
//	}

	// if trying to write the Serial number, first check to see if it has been already written
	// note this does not take count of multiple-write, thus if try to write into those reg with multiple-write, command will accept
//	if( (USART_RX_BUF[1]==WRITE_VARIABLES)  && (address<= FLASH_HARDWARE_REV) )
//	{
//		// Return false if trying to write SN Low word that has already been written
//		if(data_buffer[3] < 2)
//		{
//			if(SNWriteflag & 0x01)                // low byte of SN writed
//				return FALSE;
//		}
//		// Return false if trying to write SN High word that has already been written
//		else if (data_buffer[3] < 4)
//		{
//			if(SNWriteflag & 0x02)                 // high byte of SN writed
//				return FALSE;
//		}
//		else if (data_buffer[3] ==  FLASH_HARDWARE_REV)
//		{
//			if(SNWriteflag & 0x04)                 // hardware byte writed
//				return FALSE;
//		}

//	}


	crc_val = crc16(USART_RX_BUF, rece_size-2);

	if(crc_val == (USART_RX_BUF[rece_size-2]<<8) + USART_RX_BUF[rece_size-1] )
	{
		return 1;
	}
	else
	{
		return 0;
	}
	//return TRUE;

 }

 
 
 void dealwithData(void)
{	
	uint16_t address;
	// given this is used in multiple places, decided to put it as an argument
	address = (uint16_t)(USART_RX_BUF[2]<<8) + USART_RX_BUF[3];
	if(MODBUS_PROTOCOL == 1)
	{
			if (checkData(address))
			{		
		//		// Initialize tranmission
				initSend_COM();	
				// Initialize CRC
				init_crc16();		
		//		// Store any data being written
				internalDeal(address);
		//		// Respond with any data requested
				responseData(address);
			}
	}
	else
	{
			Response_Request(USART_RX_BUF[2]);
		
	}
		serial_restart();

}

void Response_Request(uint8_t cmd)
{
   static uint8_t  send_buf[50] ;
	 uint8_t   i ;
	  switch(cmd)
      {
         case REST_CMD:
         sprintf((char*)send_buf,"\r\nReset Done");
				 Delay(3);
				 AS1_SendBlock(AS1_ptr, send_buf, strlen((char*)send_buf))  ;
				 Delay(3);				 
         break;
         case READ_ALL_PARAMETER:
				 modbus.st_dectt  = 1 ;
         sprintf((char*)send_buf,"#C%05u P%07u TP%04d TH%04d H%04u AQ%04u\n\r", modbus.Co2, modbus.PP, modbus.PT, modbus.HT, modbus.HH, modbus.Aq);
         AS1_SendBlock(AS1_ptr, send_buf, strlen((char*)send_buf))  ;	
				 //urat_printf((char*)send_buf, strlen((char*)send_buf));
         break;
		 case READ_PM25:
         sprintf((char*)send_buf,"#PM25 %04u\n\r",modbus.PM25);
				 AS1_SendBlock(AS1_ptr, send_buf, strlen((char*)send_buf))  ;	
         break;
		 case READ_AQ :
				sprintf((char*)send_buf,"AQ%04u\n\r", modbus.Aq);
				 AS1_SendBlock(AS1_ptr, send_buf, strlen((char*)send_buf))  ;	
		 break;
		 case READ_HUM_PARAMETER :
		 sprintf((char*)send_buf,"TH%04d H%04u\n\r", modbus.HT, modbus.HH);
		 AS1_SendBlock(AS1_ptr, send_buf, strlen((char*)send_buf))  ;	
		 break ;
		 case READ_CO2_PARAMETER :
			modbus.st_dectt = 1 ;
	   sprintf((char*)send_buf,"#C%05u\n\r", modbus.Co2);
		  AS1_SendBlock(AS1_ptr, send_buf, strlen((char*)send_buf))  ;		
		 break;
		 case READ_PRESURE_PARAMETER:
		 sprintf((char*)send_buf,"P%03d TP%04d\n\r", modbus.PP, modbus.PT);
		  AS1_SendBlock(AS1_ptr, send_buf, strlen((char*)send_buf))  ;	
		 break;
		 case READ_CO2_AD_CMD:
			 modbus.st_dectt  =1 ;
		 sprintf((char*)send_buf,"\r\nAD %07u #", modbus.Co2_Ad);
			 AS1_SendBlock(AS1_ptr, send_buf, strlen((char*)send_buf))  ;	
		 break;
		 case READ_CLIBRATION_CMD:
		 sprintf((char*)send_buf,"\r\nCo2Point:%u", (unsigned int)modbus.co2_fac_point);
		 urat_printf((char*)send_buf, strlen((char*)send_buf));
		 for(i=0; i< modbus.co2_fac_point; i++)
		 {
				 sprintf((char*)send_buf,"\r\nCalPoint AD%u PPM%u",		modbus.co2_fac_ad[i], modbus.co2_fac_ppm[i] );
				  AS1_SendBlock(AS1_ptr, send_buf, strlen((char*)send_buf))  ;	 
		 }
		 break ;
		 case CALIBRATION_RESET_CMD:
		 sprintf((char*)send_buf,"\r\nCO2 calibration reset Cmd");
		 AS1_SendBlock(AS1_ptr, send_buf, strlen((char*)send_buf))  ;
		 break;
		 case STOP_DETECT:
		 sprintf((char*)send_buf,"\r\nReceive stop detect Cmd");
		 AS1_SendBlock(AS1_ptr, send_buf, strlen((char*)send_buf))  ;
		 break;
		 case READ_CO2_RTD_CMD:
		 sprintf((char*)send_buf,"\r\nRTD =%d", modbus.Rtd);
		 AS1_SendBlock(AS1_ptr, send_buf, strlen((char*)send_buf))  ;
		 break;
		 case READ_RTD_CAL_CMD:    
		 sprintf((char*)send_buf,"\r\nT0 = %d,AD0 = %u,T2 = %d, AD2 = %u",modbus.Rtd_Cal_T[0],modbus.Rtd_Cal_Ad[0],modbus.Rtd_Cal_T[1],modbus.Rtd_Cal_Ad[1]);
		 AS1_SendBlock(AS1_ptr, send_buf, strlen((char*)send_buf))  ;     
		 break;
		 case CLEAR_RTD_CAL_CMD :
		 sprintf((char*)send_buf,"\r\nClear RTD Calibration Cmd");
     AS1_SendBlock(AS1_ptr, send_buf, strlen((char*)send_buf))  ;
//		 Clear_rtd_cal_roution();
		 break;
		 case TEMP_COMPENSATION_ON:
		 sprintf((char*)send_buf,"\r\nTemperature Compensation On");
     AS1_SendBlock(AS1_ptr, send_buf, strlen((char*)send_buf))  ;
		 if(modbus.Compensation_On_Off == 0)
		 {
		 	modbus.Compensation_On_Off = 1 ;	
		// 	flash_write_int(EEP_CO2_COMPENSATION_ON_OFF, modbus.Compensation_On_Off, FLASH_MEMORY);
		 }
		 break ;
		 case TEMP_COMPENSATION_OFF:
		 sprintf((char*)send_buf,"\r\nTemperature Compensation Off");
         urat_printf((char*)send_buf, strlen((char*)send_buf));
		 if(modbus.Compensation_On_Off == 0)
		 {
		 	modbus.Compensation_On_Off = 1 ;	
	//	 	flash_write_int(EEP_CO2_COMPENSATION_ON_OFF, modbus.Compensation_On_Off, FLASH_MEMORY);
		 }
		 break;
		 case READ_HUM_TABLE:
		    sprintf((char*)send_buf,"\r\nHUMPoint:%u",(unsigned int)modbus.Hum_Cal_point);
        AS1_SendBlock(AS1_ptr, send_buf, strlen((char*)send_buf))  ;
         	for(i=0; i< modbus.Hum_Cal_point; i++)
         	{
            sprintf((char*)send_buf,"\r\nHUMPoint Meter%u Sensor%u",	modbus.Hum_MeterValue[i],	modbus.Hum_SensorValue[i]);
           AS1_SendBlock(AS1_ptr, send_buf, strlen((char*)send_buf))  ;  
         	}
		 break ; 

		 case CLEAR_HUM_TABLE :
				 sprintf((char*)send_buf,"\r\nClear Hum table");	 
         AS1_SendBlock(AS1_ptr, send_buf, strlen((char*)send_buf))  ;
					//Clear_hum_table();
		 break ;
         default:
         break;
      }	
}





void urat_printf( char* send_buf, uint16_t len)
{
		AS1_SendBlock(AS1_ptr, send_buf, len)  ;
}

