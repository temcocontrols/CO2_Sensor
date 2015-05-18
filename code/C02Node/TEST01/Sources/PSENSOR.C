#include "string.h"
#include "stdio.h"
#include "extern.h"
#include "PSENSOR.h"
#include "iic.h"
#include "modbus.h"


/* this structure holds all device specific calibration parameters */
struct bmp180_calibration_param_t{
   int16_t ac1;
   int16_t ac2;
   int16_t ac3;
   uint16_t ac4;
   uint16_t ac5;
   uint16_t ac6;
   int16_t b1;
   int16_t b2;
   int16_t mb;
   int16_t mc;
   int16_t md;
};

/* BMP180 image registers data  */
struct bmp180_t {
   struct bmp180_calibration_param_t cal_param;
   uint8_t mode;
   uint8_t chip_id, ml_version, al_version;
   uint8_t dev_addr;
   uint8_t sensortype;

   int32_t param_b5;
   int16_t number_of_samples;
   int16_t oversampling_setting;
   int16_t sw_oss;   
/*   
   BMP180_BUS_WR_RETURN_TYPE  (*bus_write)   BMP180_BUS_WR_PARAM_TYPES);
   BMP180_BUS_RD_RETURN_TYPE  (*bus_read)    (BMP180_BUS_RD_PARAM_TYPES);   
   BMP180_MDELAY_RETURN_TYPE  (*delay_msec)  (BMP180_MDELAY_DATA_TYPE);
*/  
}BMP180_TM;


/*  $Date: 2011/09/15 15:09:57 $
 *  Revision: 1.14 */
/*
* Copyright (C) 2011 Bosch Sensortec GmbH
*
* BMP180 pressure sensor API
*
* Usage:  Application Programming Interface for BMP180 configuration
*         and data read out

* Author:    venkatakrishnan.venkataraman@in.bosch.com

* Licensed under the Apache License, Version 2.0 (the "License"); you may not
  use this file except in compliance with the License and the following
  stipulations.The Apache License , Version 2.0 is applicable unless otherwise
  stated by the stipulations of the disclaimer below.

* You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

* Disclaimer

* Common:
* Bosch Sensortec products are developed for the consumer goods industry. They
* may only be used within the parameters of the respective valid product data
* sheet.Bosch Sensortec products are provided with the express understanding
* that there is no warranty of fitness for a particular purpose.They are not
* fit for use in life-sustaining, safety or security sensitive systems or any
* system or device that may lead to bodily harm or property damage if the
* system or device malfunctions. In addition,Bosch Sensortec products are not
* fit for use in products which interact with motor vehicle systems.The resale
* and/or use of products are at the purchaser's own risk and his own
* responsibility. The examination of fitness for the intended use is the sole
* responsibility of the Purchaser.
*
* The purchaser shall indemnify Bosch Sensortec from all third party claims,
* including any claims for incidental, or consequential damages, arising from
* any product use not covered by the parameters of the respective valid
* product data sheet or not approved by Bosch Sensortec and reimburse Bosch
* Sensortec for all costs in connection with such claims.
*
* The purchaser must monitor the market for the purchased products,
* particularly with regard to product safety and inform Bosch Sensortec
* without delay of all security relevant incidents.
*
* Engineering Samples are marked with an asterisk (*) or (e). Samples may vary
* from the valid technical specifications of the product series. They are
* therefore not intended or fit for resale to third parties or for use in end
* products. Their sole purpose is internal client testing. The testing of an
* engineering sample may in no way replace the testing of a product series.
* Bosch Sensortec assumes no liability for the use of engineering samples. By
* accepting the engineering samples, the Purchaser agrees to indemnify Bosch
* Sensortec from all claims arising from the use of engineering samples.
*
* Special:
* This software module (hereinafter called "Software") and any information on
* application-sheets (hereinafter called "Information") is provided free of
* charge for the sole purpose to support your application work. The Software
* and Information is subject to the following terms and conditions:
*
* The Software is specifically designed for the exclusive use for Bosch
* Sensortec products by personnel who have special experience and training. Do
* not use this Software if you do not have the proper experience or training.
*
* This Software package is provided `` as is `` and without any expressed or
* implied warranties, including without limitation, the implied warranties of
* merchantability and fitness for a particular purpose.
*
* Bosch Sensortec and their representatives and agents deny any liability for
* the functional impairment of this Software in terms of fitness, performance
* and safety. Bosch Sensortec and their representatives and agents shall not
* be liable for any direct or indirect damages or injury, except as
* otherwise stipulated in mandatory applicable law.
*
* The Information provided is believed to be accurate and reliable. Bosch
* Sensortec assumes no responsibility for the consequences of use of such
* Information nor for any infringement of patents or other rights of third
* parties which may result from its use. No license is granted by implication
* or otherwise under any patent or patent rights of Bosch. Specifications
* mentioned in the Information are subject to change without notice.
*
* It is not allowed to deliver the source code of the Software to any third
* party without permission of Bosch Sensortec.*/

/*! \file bmp180.c
    \brief This file contains all function implementations for the BMP180 API
    Details.*/

//#include "bmp180.h"
//#include "stdlibm.h"
#define  I2C_BUFFER_LEN  50         //bmp180 has 21 Regeisters

struct bmp180_t *p_bmp180;          /**< pointer to BMP180 device area */


/** initialize BMP180
  This function initializes the BMP180 pressure sensor.
  The function automatically detects the sensor type and stores this for all
  future communication and calculation steps
  param *bmp180_t pointer to bmp180 device data structure
  return result of communication routines */
unsigned char bmp180_init(void)
{
   unsigned char  comres = 0;
   unsigned char  buf = 0;
      
//   p_bmp180 = bmp180;                      /* assign BMP180 ptr */
   BMP180_TM.sensortype = E_SENSOR_NOT_DETECTED;
  // printd("\r\nsensortype %bx",BMP180_TM.sensortype);
   BMP180_TM.dev_addr = BMP180_I2C_ADDR;   /* preset BMP180 I2C_addr */
 //  printd("\r\ndev_addr %bx",BMP180_TM.dev_addr);
   comres += BMP180_BUS_READ_FUNC(BMP180_TM.dev_addr,BMP180_CHIP_ID__REG, &buf, 1);  /* read Chip Id */
//   if(buf == 0x55)printd("\r\nBus read is Ok!"); 
//   else  printd("\r\nBus read is Bad!"); 
   
   BMP180_TM.chip_id = ((buf & BMP180_CHIP_ID__MSK) >> BMP180_CHIP_ID__POS);  /* macro define ## */
 //  printd("\r\nchip_id %bx",BMP180_TM.chip_id);     
   BMP180_TM.number_of_samples = 1;
   /* ultra high resolution */
   BMP180_TM.oversampling_setting = 3;   
   /*the oversampling ratio of the pressure measurement 
   (00b: single, 01b: 2 times, 10b: 4 times, 11b: 8 times)*/
   BMP180_TM.sw_oss = 1;
   if (BMP180_TM.chip_id == BMP180_CHIP_ID) {
      /* get bitslice */
      BMP180_TM.sensortype = BOSCH_PRESSURE_BMP180;
      /* read Version reg */
      comres += BMP180_BUS_READ_FUNC(BMP180_TM.dev_addr, BMP180_VERSION_REG, &buf, 1);
	//  printd("\r\nBMP180_VERSION = %u", (unsigned int)buf);
      /* get ML Version */
      BMP180_TM.ml_version = ((buf & BMP180_ML_VERSION__MSK) >> BMP180_ML_VERSION__POS);                                                                                                                                              
      /* get AL Version */
      BMP180_TM.al_version = ((buf & BMP180_AL_VERSION__MSK) >> BMP180_AL_VERSION__POS);
      /*readout bmp180 calibparam structure*/                                   
      bmp180_get_cal_param(); 
   }
      
   p_bmp180 = &BMP180_TM;
 //  printd("\r\nBmp Init Finish!");
/*
   if(p_bmp180 == NULL)
      {
         printf("\r\nNot assign a ptr..");
         return 0;
      }
   else  
   printf("\r\ninit bmp180 ok..");
*/   
   return comres;
}


/** read out parameters cal_param from BMP180 memory
    return result of communication routines*/
unsigned char bmp180_get_cal_param(void)
{
  // unsigned int xdata i ;
   unsigned char  comres;
   unsigned char  buf[22];  
   
 //  printd("get param \n\r");   
   comres = BMP180_BUS_READ_FUNC(BMP180_TM.dev_addr,BMP180_PROM_START__ADDR, buf, BMP180_PROM_DATA__LEN);
   
//   unsigned char i;
//   for(i = 0; i < BMP180_PROM_DATA__LEN; i++)
//   {
//      BMP180_BUS_READ_FUNC(BMP180_TM.dev_addr,(BMP180_PROM_START__ADDR+i), (buf+i), 1);
//	  printd("\n\rBUF[%d] = %bx",i,buf[i]);     
//   }
     
   /*parameters AC1-AC6*/ 
   BMP180_TM.cal_param.ac1 =  ((uint16_t)buf[0] << 8) + buf[1];
   BMP180_TM.cal_param.ac2 =  ((uint16_t)buf[2] << 8) + buf[3];
   BMP180_TM.cal_param.ac3 =  ((uint16_t)buf[4] << 8) + buf[5];
   BMP180_TM.cal_param.ac4 =  ((uint16_t)buf[6] << 8) + buf[7];
   BMP180_TM.cal_param.ac5 =  ((uint16_t)buf[8] << 8) + buf[9];
   BMP180_TM.cal_param.ac6 =  ((uint16_t)buf[10] << 8) + buf[11];

   /*parameters B1,B2*/
   BMP180_TM.cal_param.b1 =  ((uint16_t)buf[12] << 8) + buf[13];
   BMP180_TM.cal_param.b2 =  ((uint16_t)buf[14] << 8) + buf[15];

   /*parameters MB,MC,MD*/
   BMP180_TM.cal_param.mb =  ((uint16_t)buf[16] << 8) + buf[17];
   BMP180_TM.cal_param.mc =  ((uint16_t)buf[18] << 8) + buf[19];
   BMP180_TM.cal_param.md =  ((uint16_t)buf[20] << 8) + buf[21];


//   printd("\r\nac1 %x",BMP180_TM.cal_param.ac1);
//   printd("\r\nac2 %x",BMP180_TM.cal_param.ac2);
//   printd("\r\nac3 %x",BMP180_TM.cal_param.ac3);
//   printd("\r\nac4 %x",BMP180_TM.cal_param.ac4);
//   printd("\r\nac5 %x",BMP180_TM.cal_param.ac5);
//   printd("\r\nac6 %x",BMP180_TM.cal_param.ac6);
//   printd("\r\n b1 %x",BMP180_TM.cal_param.b1);
//   printd("\r\n b2 %x",BMP180_TM.cal_param.b2);
//   printd("\r\n mb %x",BMP180_TM.cal_param.mb);
//   printd("\r\n mc %x",BMP180_TM.cal_param.mc);
//   printd("\r\n md %x",BMP180_TM.cal_param.md);
          
   return comres;
}

/** calculate temperature from ut
  ut was read from the device via I2C and fed into the
  right calc path for BMP180
  \param ut parameter ut read from device
  \return temperature in steps of 0.1 deg celsius
  \see bmp180_read_ut()*/
int16_t bmp180_get_temperature(uint32_t ut)
{
   int16_t  temperature;
   int32_t  x1, x2;
		int8_t str[30] ;
//   signed int32 x3, x4;
//   printf("\r\nut %ld",ut);
   if (p_bmp180->sensortype == BOSCH_PRESSURE_BMP180) {
//      sprintf(str, "ut=%u\n\r", (int32_t)ut);	 
//			AS2_SendBlock(AS2_ptr, str, strlen(str))  ;
//		  Delay(10);
      x1 = ((( int32_t) ut - (int32_t) p_bmp180->cal_param.ac6) * (int32_t) p_bmp180->cal_param.ac5) >> 15;          
/*      
      printf("\r\nac5 %ld",p_bmp180->cal_param.ac5);
      printf("\r\nac6 %ld",p_bmp180->cal_param.ac6);      
      printf("\r\nx1 %lx",x1);

      x3 = (signed int32) (p_bmp180->cal_param.mc);
      printf("\r\nx3 %lx",x3);
      x3 = x3 << 11;
      printf("\r\nx3 %ld",x3);
      x4 = (signed int32) (p_bmp180->cal_param.md);
      printf("\r\nx4 %ld",x4);
      x4 = x4 + x1;
      printf("\r\nx4 %ld",x4);
      x2 = x3 / x4;
*/      
      x2 = ((int32_t) p_bmp180->cal_param.mc << 11) / (x1 + p_bmp180->cal_param.md);             
/*
      printf("\r\nmc %ld",p_bmp180->cal_param.mc);
      printf("\r\nmd %ld",p_bmp180->cal_param.md);      
      printf("\r\nx2 %lx",x2);
*/
      p_bmp180->param_b5 = x1 + x2;
//      printf("\r\nb5 %Ld",p_bmp180->param_b5);        
   }
   
   temperature = ((p_bmp180->param_b5 + 8) >> 4); 
   /* temperature in 0.1 deg C */
   sprintf(str, "PT=%d\n\r", (int16_t)temperature);	 
	 AS2_SendBlock(AS2_ptr, str, strlen(str))  ;
	 Delay(2);
   return temperature;
}

signed long Shift_Right_32bit(signed long value,unsigned char num)
{
   unsigned char  i;
   
   if(value & 0x8000000)
   {
//      printf("\r\nvalue %Lx",value);
      for(i = 0; i < num; i++)
      {
         value >>= 1;
         value |= 0x80000000; 
//         printf("\r\nvalue %Lx",value);
      }     
   }
   else{
      
      value >>= num;
   }

   return value;   
}

/** calculate pressure from up
  up was read from the device via I2C and fed into the
  right calc path for BMP180
  In case of BMP180 averaging is done through oversampling by the sensor IC

  \param ut parameter ut read from device
  \return temperature in steps of 1.0 Pa
  \see bmp180_read_up()*/
int32_t bmp180_get_pressure(uint32_t up)         /* shift operator has bug signed right shift 0 >> */
{
   int32_t  pressure, x1, x2, x3, b3, b6;
   uint32_t   b4, b7;
		int8_t str[30] ;
   b6 = p_bmp180->param_b5 - 4000;
//   printf("\r\nb5 %Ld",p_bmp180->param_b5);
//   printf("\r\nb6 %Ld",b6);
   /*****calculate B3************/
   x1 = (b6 * b6) >> 12;
//   printf("\r\nx1 %Ld",x1);
   x1 *= p_bmp180->cal_param.b2;   
//   x1 >>= 11;  
   x1 = Shift_Right_32bit(x1,11);
//   printf("\r\nx1 %Ld",x1);

   x2 = (p_bmp180->cal_param.ac2 * b6);
//   x2 >>= 11;  
   x2 = Shift_Right_32bit(x2,11);
//   printf("\r\nx2 %Ld",x2);

   x3 = x1 + x2;
//   printf("\r\nx3 %Ld",x3);
   b3 = (((((int32_t)p_bmp180->cal_param.ac1)*4 + x3) << p_bmp180->oversampling_setting) + 2) / 4;  
//   printf("\r\nac1 %Ld",p_bmp180->cal_param.ac1);
//   printf("\r\nb3 %Ld",b3);
   
   /*****calculate B4************/
   x1 = p_bmp180->cal_param.ac3 * b6 ; 
   x1 = Shift_Right_32bit(x1,13);
//   printf("\r\nx1 %Ld",x1);
   x2 = p_bmp180->cal_param.b1 * ((b6 * b6) >> 12);
   x2 = Shift_Right_32bit(x2,16);
   x2 = b6 * b6 ;
//  printf("\r\nx2 %Ld",x2);
   x2 = Shift_Right_32bit(x2,12);
   x2 = x2 * p_bmp180->cal_param.b1 ;
//   printf("\r\nx2 %Ld",x2);
//   x2 = x2 >> 16;
   x2 = Shift_Right_32bit(x2,16);
//   printf("\r\nx2 %Ld",x2);
   x3 = ((x1 + x2) + 2) / 4;
//   printf("\r\nx3 %Ld",x3);
   b4 = p_bmp180->cal_param.ac4 * (uint32_t) (x3 + 32768) ; 
   b4 = Shift_Right_32bit(b4,15);
//   printf("\r\nb4 %Ld",b4);

   b7 = ((uint32_t)(up - b3) * (50000 >> p_bmp180->oversampling_setting));
//   printf("\r\nb7 %Ld",b7);
   
   
   if (b7 < 0x80000000)
      pressure = (b7 << 1) / b4;
   else
      pressure = (b7 / b4) << 1;
      
//   printf("\r\npressure %Ld",pressure);        
      

//   x1 = pressure >> 8;
   x1 = Shift_Right_32bit(pressure,8);
//   printf("\r\nx1 %Ld",x1);
   x1 *= x1;
//  printf("\r\nx1 %Ld",x1);
   x1 = (x1 * PARAM_MG) >> 16 ;           /* PARAM_MG = 3038 */
//   printf("\r\nx1 %Ld",x1);
   x2 = pressure * PARAM_MH  ;   /* PARAM_MH = -7357 */
   x2 = Shift_Right_32bit(x2,16);
   x2 = pressure * PARAM_MH ; 
//   printf("\r\nx2 %Ld",x2);
//   x2 /= 65536 ; /* >> 16 */
   x2 = Shift_Right_32bit(x2,16);
//   printf("\r\nx2 %Ld",x2);
   /* pressure in Pa*/
   pressure += (x1 + x2 + PARAM_MI) / 16 ;  /* PARAM_MI = 3791 */
   
//   x1 = x1 + x2 + PARAM_MI;
//   x1 = x1 / 16;   
//   printf("\r\nx1 %Ld",x1);   
//   pressure += x1;   
//   printf("\r\nPressure  %LdPa",pressure);
   sprintf(str, "PP=%u\n\r", (uint32_t)pressure);	 
	 AS2_SendBlock(AS2_ptr, str, strlen(str))  ;
	 Delay(2);
   return pressure;
}


/** read out ut for temperature conversion
    return ut parameter that represents the uncompensated
    temperature sensors conversion value*/
uint16_t bmp180_get_ut()
{
   uint16_t  ut;
   uint8_t  buf[2];
   uint8_t  ctrl_reg_data;
   uint16_t  wait_time;
   uint8_t  comres;
	int8_t  str[20];
//   unsigned int16 a1 = 0x0000, a2 = 0x0000;
   if (p_bmp180->chip_id == BMP180_CHIP_ID) /* get bitslice */
   {
      ctrl_reg_data = BMP180_T_MEASURE;
      wait_time = BMP180_TEMP_CONVERSION_TIME;      
//    printf("\r\nwait time 5ms..");
   }
   comres = BMP180_BUS_WRITE_FUNC(p_bmp180->dev_addr,BMP180_CTRL_MEAS_REG, &ctrl_reg_data, 1);
   Delay(wait_time);
  comres += BMP180_BUS_READ_FUNC(p_bmp180->dev_addr,BMP180_ADC_OUT_MSB_REG, buf, 2); 


	 
	 //   printf("\r\ndata1 %x",data[0]);
//   printf("\r\ndata2 %x",data[1]);
        
   ut = ((uint16_t)buf[0] << 8) + buf[1];
//   sprintf(str, "ut=%u\n\r", (uint16_t)ut);	 
//	 AS2_SendBlock(AS2_ptr, str, strlen(str))  ;
//	 Delay(10);
	 
   return ut;
}


/** read out up for pressure conversion
    depending on the oversampling ratio setting up can be 16 to 19 bit
    return up parameter that represents the uncompensated pressure value*/
uint32_t bmp180_get_up()
{
   uint16_t  j;         /* j included for loop */
   uint32_t  up = 0;
   uint32_t  sum = 0;   /* get the calculated pressure data */
   uint8_t  buf[3];
   uint8_t  ctrl_reg_data;
   uint8_t  comres = 0;
   if (p_bmp180->chip_id == BMP180_CHIP_ID &&
                     p_bmp180->sw_oss == 1 &&                     
                     p_bmp180->oversampling_setting == 3) {
      for (j = 0 ; j < 3; j++) {
            /* 3 times getting pressure data*/
            ctrl_reg_data = BMP180_P_MEASURE + (p_bmp180->oversampling_setting << 6);
            comres = BMP180_BUS_WRITE_FUNC(p_bmp180->dev_addr, BMP180_CTRL_MEAS_REG, &ctrl_reg_data, 1);
            Delay(2 + (3 << (p_bmp180->oversampling_setting)));
            comres += BMP180_BUS_READ_FUNC(p_bmp180->dev_addr, BMP180_ADC_OUT_MSB_REG,buf, 3);
            sum = (((uint32_t) buf[0] << 16)|
                   ((uint32_t) buf[1] << 8) |
                     (uint32_t) buf[2]) >> (8 - p_bmp180->oversampling_setting);
            p_bmp180->number_of_samples = 1;
//            printf("\r\nsum %Lx",sum);
            up = up + sum;  /*add up with dummy var*/
      }
         up = up / 3;       /* averaging */
//         printf("\r\nup %Lx",up);
   }
  else{
//      printf("\r\nstep");
      if (p_bmp180->chip_id == BMP180_CHIP_ID && p_bmp180->sw_oss == 0){
      ctrl_reg_data = BMP180_P_MEASURE + (p_bmp180->oversampling_setting << 6);
      comres = BMP180_BUS_WRITE_FUNC(p_bmp180->dev_addr,BMP180_CTRL_MEAS_REG, &ctrl_reg_data, 1);
      Delay(2 + (3 << (p_bmp180->oversampling_setting)));
      comres += BMP180_BUS_READ_FUNC(p_bmp180->dev_addr,BMP180_ADC_OUT_MSB_REG, buf, 3);
      up = (((uint32_t) buf[0] << 16) |
            ((uint32_t) buf[1] << 8)  |
              (uint32_t) buf[2]) >> (8 - p_bmp180->oversampling_setting);
      p_bmp180->number_of_samples = 1;
      }
    }
return up;
}



unsigned char BMP180_BUS_READ_FUNC(unsigned char device_addr, unsigned char reg_addr, unsigned char *reg_data, unsigned char cnt)
{   

   unsigned char iError=0;
//   unsigned char array[I2C_BUFFER_LEN];
//   unsigned char stringpos;   
   
//   iError = I2C_read_string(device_addr, reg_addr, array, cnt);
   iError = I2C_read_string(device_addr, reg_addr, reg_data, cnt);
      
//   for(stringpos = 0; stringpos < cnt; stringpos++)
//      *(reg_data + stringpos) = array[stringpos];
      
   return iError;  
  
}

unsigned char BMP180_BUS_WRITE_FUNC(unsigned char device_addr, unsigned char reg_addr, unsigned char *reg_data, unsigned char cnt)
{ 
   
   unsigned char  iError=0;
//   unsigned char array[I2C_BUFFER_LEN];
//   unsigned char stringpos;   
   
//   for(stringpos = 0; stringpos < cnt; stringpos++)
//      array[stringpos+1] = *(reg_data + stringpos);
      
   iError = I2C_write_string(device_addr, reg_addr, reg_data, cnt);
   return iError; 
  
}

//void delay_msec(int16 tick)                     //Millisecond
//{  
//  delay_ms(tick);
//}


unsigned char I2C_read_string(unsigned char device_addr, unsigned char reg_addr, unsigned char *array, unsigned char cnt)
{
   unsigned char  i, value;
  // i2c_start();
   value = iic_start(device_addr & 0xfe);       //addr + W
      if(value){ 
				AS2_SendBlock(AS2_ptr, "\r\n read addr fail", strlen("\r\n read addr fail"))  ;
				Delay(10);
				return 0;
			}
   value = iic_writebyte(reg_addr);      
     if(value){ 
				AS2_SendBlock(AS2_ptr, "\r\n read reg fail", strlen("\r\n read reg fail"))  ;
				Delay(10);
			 return 0;
			}
 //  i2c_start();                                //restart   
   value = iic_restart(device_addr | 0x01);      //addr + R
     if(value){ 
				AS2_SendBlock(AS2_ptr, "\r\n restart fail", strlen("\r\n restart fail"))  ;
				Delay(10);
			  return 0;
			}
   for(i = 0; i < cnt - 1 ; i++)
   {          
     *array = iic_readbyte(d_ACK);                      
      array++;
   }
   
   *array = iic_readbyte(d_NACK);   
        
   iic_stop();
   
   return 1;
}


unsigned char I2C_write_string(unsigned char device_addr, unsigned char reg_addr, unsigned char *array, unsigned char cnt)
{
   unsigned char  i, value;
   
//   i2c_start();
   value = iic_start(device_addr & 0xfe);      //addr + W
      if(value){ 
				AS2_SendBlock(AS2_ptr, "\r\n write addr fail", strlen("\r\n write addr fail"))  ;
				Delay(10);
				return 0;
			}
   value = iic_writebyte(reg_addr);
      if(value){
      AS2_SendBlock(AS2_ptr, "\r\n write Reg", strlen("\r\n write Reg"))  ;
				Delay(10);
      return 0;}
   for(i = 0; i < cnt; i++)
   {
      value = iic_writebyte(*array);
    if(value){
      AS2_SendBlock(AS2_ptr, "\r\n write arr error", strlen("\r\n write arr error"))  ;
			Delay(10);
			return 0;}
     array++;
   }  
   iic_stop();
   
   return 1;
}


void Press_Task(void)
{
	uint16_t  UT = 0;
	uint32_t   UP = 0 ; 
	 UT = bmp180_get_ut();
   UP = bmp180_get_up();               
   modbus.PT = bmp180_get_temperature((uint32_t) UT);
	 modbus.PP = bmp180_get_pressure(UP);

//	 sprintf(str, "PP=%u\n\r", modbus.PS);
//	 Delay(20);
//	 AS2_SendBlock(AS2_ptr, str, strlen(str))  ;
//	 Delay(20);
//	 modbus.PS = modbus.PS /10000;
	// printd("\n\rP_T =%d PS =%lu",modbus.T_P,modbus.PS);
}
