
#include "iic.h"
#include "htu21.h"
#include "modbus.h"
#include "extern.h"
#include "caculate.h"
uint8_t htu21d_write_user_register(uint8_t bit_index, uint8_t bit_value)
{
   uint8_t reg_tmp;
  
   iic_start(DEV_ADDR | I2C_WR);
   iic_writebyte(CMD_READ_USER_REGISTER);
   iic_restart(DEV_ADDR | I2C_RD);
   reg_tmp = iic_readbyte(0);
   if(bit_value == 1)
      reg_tmp |= ((int8_t)1 << bit_index);
   else
      reg_tmp &= ~((int8_t)1 << bit_index);
   	iic_start(DEV_ADDR | I2C_WR);
	iic_writebyte(CMD_WRITE_USER_REGISTER);
	iic_writebyte(reg_tmp);
    iic_stop();
  	 return 1;
   

   /*
   ack = iic_writebyte(CMD_READ_USER_REGISTER);
   if(ack == 1) // no ack
   {
      iic_stop();
      return 0;
   }
   
   iic_start();
   ack = iic_writebyte(DEV_ADDR | I2C_RD);
   if(ack == 1) // no ack
   {
      iic_stop();
      return 0;
   }
   
   reg_tmp = iic_readbyte(0);
   if(bit_value == 1)
      reg_tmp |= ((int8)1 << bit_index);
   else
      reg_tmp &= ~((int8)1 << bit_index);
   
   iic_start();
   ack = iic_writebyte(DEV_ADDR | I2C_WR);
   if(ack == 1) // no ack
   {
      iic_stop();
      return 0;
   }
   
   ack = iic_writebyte(CMD_WRITE_USER_REGISTER);
   if(ack == 1) // no ack
   {
      iic_stop();
      return 0;
   }
     
   ack = iic_writebyte(reg_tmp);
   if(ack == 1) // no ack
   {
      iic_stop();
      return 0;
   }
   
   iic_stop();
   return 1;*/
}

uint8_t htu21d_soft_reset(void)
{
   iic_start(DEV_ADDR | I2C_WR);
   iic_writebyte(CMD_SOFT_RESET);  
   iic_stop();
   return 1;
}


uint8_t htu21d_trigger_measurement_no_hold_master(uint8_t type)
{
   iic_start(DEV_ADDR | I2C_WR);
  
   if(type == SELECT_TEMP)
      iic_writebyte(CMD_TRIGGER_TEMP_NO_HOLD_MASTER);
   else
      iic_writebyte(CMD_TRIGGER_HUM_NO_HOLD_MASTER); 
   iic_stop();
   return 1;
}

uint8_t htu21d_read_measurement_no_hold_master(uint8_t type, uint16_t *value)
{

   uint16_t temp = 0;
   
   iic_start(DEV_ADDR | I2C_RD);
  
   temp = iic_readbyte(d_ACK);
   temp <<= 8;
   temp |= iic_readbyte(d_ACK);
   
   iic_readbyte(d_NACK); // crc, ignore this byte
   
   iic_stop();
   *value = temp;
   return (uint8_t)1;
}

uint8_t htu21d_calculation(uint8_t type, uint16_t src, int16_t *dst)
{
   int32_t ret;
  /* if(type != (src & 0x0002))
      return 0;	*/
   
   ret = (int32_t)(src & 0xfffc);
   
   if(type == SELECT_TEMP)
   {
      ret = ret * 17572;
      //ret >>= 16;
      ret /= 65536;
      *dst = (int32_t)(ret - 4685);
      *dst = *dst / 10;
      
   }
   else
   {
      ret = ret * 1250;
      //ret >>= 16;
      ret /= 65536;
      *dst = (int32_t)(ret - 60);
   }
   
   return 1;
}




void HTU21_TASK(void)
{
	  static uint8_t   state = TRIGGER_HUM ;
	  static uint8_t    retry_times = 0 ;
	  int16_t   dst_buffer;
	  uint16_t  src_buffer;
	  uint16_t  humidity_buf ;
	  int16_t   temperature_buf = 0 ;
		char str[20] ;
	  switch(state)
      {
         case TRIGGER_HUM:
            if(htu21d_trigger_measurement_no_hold_master(SELECT_HUM))
            {
               state = READ_HUM;
               retry_times = 0;
            }
            else
            {
               retry_times++;
               if(retry_times >= 5)
               {
                  state = READ_TEMP;
									retry_times =0 ;
               }
            }
            break;
         case TRIGGER_TEMP:
            if(htu21d_trigger_measurement_no_hold_master(SELECT_TEMP))
            {
               state = READ_TEMP;
               retry_times = 0;
            }
            else
            {
               retry_times++;
               if(retry_times >= 5)
               {
                  state = READ_HUM;
				  retry_times =0 ;
               }
            }
            break;
         case READ_HUM:
            if(htu21d_read_measurement_no_hold_master(SELECT_HUM, &src_buffer))
            {
               //printd("Read HUM success src_buffer =0x%x\n\r" ,src_buffer);
							 if(htu21d_calculation(SELECT_HUM, src_buffer, &dst_buffer))
               {
									humidity_buf = dst_buffer;            
									modbus.HH =	 Calculate(humidity_buf, modbus.Hum_SensorValue, modbus.Hum_MeterValue, modbus.Hum_Cal_point);	
								  sprintf(str, "HH=%u\n\r", (uint16_t)modbus.HH);
									AS2_SendBlock(AS2_ptr, str, strlen(str))  ;
								  Delay(3);
               }
               state = TRIGGER_TEMP;
			  // state = TRIGGER_HUM;
               retry_times = 0;
            }
            else
            {
               retry_times++;
               if(retry_times >= 5)
               {
									state = READ_TEMP;
									retry_times = 0 ;
               }
            }
            break;
         case READ_TEMP:
            if(htu21d_read_measurement_no_hold_master(SELECT_TEMP, &src_buffer))
            {
               //printd("Read Temp success src_buffer =0x%x\n\r" ,src_buffer);
			   if(htu21d_calculation(SELECT_TEMP, src_buffer, &dst_buffer))
               {
                  temperature_buf =  dst_buffer ;
									modbus.HT =   temperature_buf ;
								 sprintf(str, "HT=%u\n\r", (uint16_t)modbus.HT);
								 AS2_SendBlock(AS2_ptr, str, strlen(str))  ;
								 Delay(5);
				 // printd("\n\rH_T = %d Hum = %u", modbus.H_Temp,modbus.Hum);
				  //temperature_buf = dst_buffer;
                  //temperature_value = temperature_buf + temperature_calibration;
               }
               state = TRIGGER_HUM;
               retry_times = 0;
            }
            else
            {
               retry_times++;
               if(retry_times >= 5)
               {
                  state = READ_HUM;
				  retry_times = 0 ;
               }
            }
            break; 
         default:
            break;
      }	
}


////uint16_t Hum_Cal_Roution(uint16_t Hum_Buf)
////{
//// 	uint16_t  Hum ;
////	uint8_t   Loop ;
////	if(modbus.Hum_Cal_point <2)
////	{
////		Hum = Hum_Buf ;
////		return Hum ;
////	}
////	if(Hum_Buf >= modbus.Hum_Read_Value[modbus.Hum_Cal_point -1])
////	{
////		Hum =  (Hum_Buf *(modbus.Hum_Real_Value[modbus.Hum_Cal_point -1] - modbus.Hum_Real_Value[modbus.Hum_Cal_point -2])+ modbus.Hum_Read_Value[modbus.Hum_Cal_point -1]*modbus.Hum_Real_Value[modbus.Hum_Cal_point -2] - modbus.Hum_Read_Value[modbus.Hum_Cal_point -2]*modbus.Hum_Real_Value[modbus.Hum_Cal_point -1])/(modbus.Hum_Read_Value[modbus.Hum_Cal_point -2] +modbus.Hum_Read_Value[modbus.Hum_Cal_point -1]);
////	}
////	else if(Hum_Buf <= modbus.Hum_Read_Value[0])
////	{
////		Hum =  (Hum_Buf *(modbus.Hum_Real_Value[1] - modbus.Hum_Real_Value[0])+ modbus.Hum_Read_Value[1]*modbus.Hum_Real_Value[0] - modbus.Hum_Read_Value[0]*modbus.Hum_Real_Value[1])/(modbus.Hum_Read_Value[0] +modbus.Hum_Read_Value[1]);	
////	}
////	else
////	{ 	
////		Loop = 0 ;
////		while(1)
////		{
////			if(Hum_Buf >modbus.Hum_Read_Value[Loop])
////			{
////				Loop++;	
////			}
////			else
////			{
////				break;
////			}	
////		}
////		Hum =  (Hum_Buf *(modbus.Hum_Real_Value[Loop -1] - modbus.Hum_Real_Value[Loop -2])+ modbus.Hum_Read_Value[Loop -1]*modbus.Hum_Real_Value[Loop -2] - modbus.Hum_Read_Value[Loop -2]*modbus.Hum_Real_Value[Loop -1])/(modbus.Hum_Read_Value[Loop -2] +modbus.Hum_Read_Value[Loop -1]);
////	}
////	return 	Hum ;
////	
////}


////void Clear_hum_table(void)
////{
////	unsigned char idata i ;
////	modbus.Hum_Cal_point = 0 ;
////	flash_write_int(EEP_HUM_CAL_POINTS, modbus.Hum_Cal_point, FLASH_MEMORY);
////	for(i=0; i<modbus.Hum_Cal_point;  i++)
////	{
////		modbus.Hum_Read_Value[i] = 0 ;
////		modbus.Hum_Real_Value[i] = 0 ;
////		flash_write_int(EEP_HUM_READ_VALUE0+2*i, modbus.Hum_Read_Value[i], FLASH_MEMORY);
////		flash_write_int(EEP_HUM_METER_VALUE0+2*i, modbus.Hum_Real_Value[i], FLASH_MEMORY);	
////	}	

////}

