#include "extern.h"
#include "modbus.h"
#include "caculate.h"

uint8_t As2_str[50];


int16_t Calculate(uint16_t data_in, uint16_t * x_axis, uint16_t* y_axis, uint16_t point)
{
	int16_t data_out = 0 ;
	uint8_t  Loop ;
	uint16_t Y1, Y2 ;
	uint16_t  X1 , X2 ;

	if(point < 2)
	{
		AS2_SendBlock(AS2_ptr, "point < 2\n\r", strlen("point < 2\n\r"))  ;
		return data_in ;
	}
	//if(Ad >co2_buf[(modbus.Co2_Cal_Point-1)].Cal_ad_value)	//((x - x1)*y2 -(x2 - x)*y1)/(x2 - x1) //ad reading is too big and out of calibration range, we use the last two biggest calibration ponits to calculate the ppm
	if(data_in > x_axis[point - 1])
	{
		X2 = x_axis[point - 1] ;
		X1 = x_axis[point - 2] ;
		Y2 = y_axis[point - 1] ;
		Y1 = y_axis[point - 2] ;
		
	}
	else if(data_in <x_axis[0]) 		//ad reading is too small and out of calibration range, we use the first two smallest calibration ponits to calculate the ppm
	{	
		X2 = x_axis[1] ;
		X1 = x_axis[0] ;
		Y2 = y_axis[1] ;
		Y1 = y_axis[0] ;
	}
	else
	{	
		Loop = 0 ;
		while(1)
		{
			if(data_in >x_axis[Loop])
			{
				Loop++;	
			}
			else
			{
				break;
			}	
		}
		X2 = x_axis[Loop] ;
		X1 = x_axis[Loop - 1] ;
		Y2 = y_axis[Loop] ;
		Y1 = y_axis[Loop - 1] ;
	}
	sprintf((char*)As2_str, "X1=%u X2=%u Y1=%u Y2=%u\n\r", X1,X2,Y1,Y2);
	AS2_SendBlock(AS2_ptr, As2_str, strlen((char*)As2_str))  ;
	//data_out = (int16_t)( ((int32_t)A2 - data_in)*B1-((int32_t)A1 -data_in)*B2)/(A2-A1);
	data_out = (Y1*((int32_t)X2 - data_in)+ Y2*((int32_t)data_in - X1))/(X2 - X1) ;
	if(data_out <0) data_out = 0 ;

	return data_out ;
}

//data_out = (Y1*(X2 - data_in)+ Y2*(data_in - X1))/(X2 - X1) ;

uint16_t Filter(uint16_t input)
{
	// -------------FILTERING------------------
	int16_t  siDelta = 0;
	uint16_t  uiResult = 0;
  int16_t  uiTemp = 0;
	static uint32_t  analog_in_buffer = 0 ;
	//static uint8_t  bigchange_count = 0 ;
	
	uiTemp = input;  
	siDelta = uiTemp - analog_in_buffer;    //compare new reading and old reading
	 //If the difference in new reading and old reading is greater than 5 degrees, implement rough filtering.
  if (( siDelta >= 100 ) || ( siDelta <= -100)) // deg f
	  	analog_in_buffer = analog_in_buffer + (siDelta >> 2);//1 	
	// Otherwise, implement fine filtering.		
	else
	{
	  analog_in_buffer =   modbus.filter*analog_in_buffer ;
		analog_in_buffer += (uint32_t)uiTemp;
	 	analog_in_buffer = (uint16_t)(analog_in_buffer/(modbus.filter+1));			 	 
	}
	uiResult = analog_in_buffer; 
 
	return uiResult;	
}




