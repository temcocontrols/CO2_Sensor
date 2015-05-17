#include "extern.h"
#include "modbus.h"
#include "aq.h" 



uint16_t  aq_value = 0 ;
uint16_t aq_calibration =0 ;

int16_t  Aq_Temp = 0 ;


uint8_t const air_cal_point[4] = {20,30,55,100};
//unsigned int16  analog_calibration[2];
uint16_t look_up_hummity_temp_table(uint16_t hum_temp,uint16_t tmper);  
uint16_t  base_air_q,now_aq;
uint16_t aq_buffer;//ervery time read aq
uint16_t eight_min_ch=0;
uint16_t aq_level=AQ_CLEAN_STATE;
uint8_t  air_up=0;
uint16_t const  temp_hummity_for_aq[][3]={
               /*40%  65%   85%*/   
               {161,142,125},//10
               {130,100, 93},//20
               { 99, 80, 70},//30
               { 78, 61, 54},//40
               { 63, 48, 43} //50
                                    };



//float const  R0[]={0.65,0.53,0.43,0.38};
uint16_t const  hummity_talbe[]={400,650,850};
uint16_t  show_aq_sen=99;
uint16_t const  temperture_talbe[]={100,200,300,400,500};
uint8_t   run_check_aq=0; 

uint16_t  aq_analog_input  ;

// *************************************************************************************
//   check the air quality of things
//      must call this routine each time there is a new sensor reading
// *************************************************************************************
void check_Air_Quality(void)
{
   
   static  uint16_t  aq_bu[40],max_data ,min_data;
   static uint16_t  temper_back[2],hummity_back[2];
   static uint8_t k=0,i=0;
  
   uint16_t temp;       
   uint16_t   RA;
   uint8_t 	j;
   
   float   RS1,RS2;      
   float   rs_cel=1;
   uint16_t  now_aq_error,max_min_error;
//   static unsigned int xdata hummity[2],temper[2];



   /*
      if the model open after 6~7min 
   */
   if(run_check_aq==INIT_AQ)
   {
      
 //     aq_buffer=aq_analog_input;
//      aq_bu[0]=now_aq;  
      i++;
      if(((now_aq-aq_analog_input)<8)||((aq_analog_input-now_aq)<8)||(i>150))//5 mins to decide if it is stable
      {
         run_check_aq=AQ_CHECK;
         i=0;
      }
      now_aq=aq_analog_input;
      base_air_q = aq_analog_input;    
      
   }
   else 
   {
      
      if(k&&(aq_level>AQ_CLEAN_STATE)&&(modbus.HH>100))
      {
         rs_cel=now_aq/20;
         RA=(50-rs_cel*10)/rs_cel; 
       
                                            
       
       RS1=RA/30.0;
          RS1=look_up_hummity_temp_table(hummity_back[0],temper_back[0])*RS1/100;
         RS2=RA/30.0;
          RS2=look_up_hummity_temp_table(hummity_back[1],temper_back[1])*RS2/100;
         if(RS2<RS1*0.83)
         {
            temp=(50/(RA*RS2+10)-50/(RA*RS1+10))*20+min_data;//celbration
            if((max_data-temp<air_cal_point[0]-AIR_POLLUTE_PASS)||max_data<temp)   
            {
               now_aq=max_data;
               aq_level=AQ_CLEAN_STATE;
            }
         }
      }
   
      
      if(base_air_q>aq_analog_input)
         base_air_q=aq_analog_input;   //the min of input
      
      i++;
   
      if(i>=alarm_delay)
      {
         k=1;
         i=0;
         temper_back[0]=Aq_Temp;   
         hummity_back[0]=modbus.HH;
      }
      
      aq_buffer = aq_analog_input;
      aq_bu[i]=aq_buffer;
      
      if(i==(alarm_delay-1))
      {
         temper_back[1]=Aq_Temp;   
         hummity_back[1]=modbus.HH;
      }

      
         /*
            every 8 mins change the air base 
         */
      eight_min_ch++;
      if((eight_min_ch>AQ_UP_TIME)&&(air_up==1)) //if polluted >= level3 ,every 8 mins   ,the minest of aq_input
      {
         air_up=0;
         eight_min_ch=0;
         now_aq=base_air_q;
         base_air_q=0x3FF;
      }

         
      if((eight_min_ch>AQ_TIME)&&(aq_level==0))//if polluted ,we cannot change the base air   ,every 5 mins,the minest of aq input
      {
         eight_min_ch=0;
         
      
         now_aq=base_air_q;//put the low in the before time as aq base 
            
         base_air_q=0x3FF;
      }
      
      if(k&&(aq_buffer>now_aq))//after first collection
      {
         ////////////////////
            max_data=aq_bu[0];
            min_data = aq_bu[0];
            for(j=0;j<alarm_delay;j++)          //max        //?    
            { 
   
                if(max_data<aq_bu[j])  
                {
                   max_data=aq_bu[j];           //the max value
                }
             else  
                {
                   min_data=aq_bu[j];           //the min value
                }  
            } 
              
            if(min_data<=now_aq)
               min_data=now_aq;
             /////////////////////////////////
           now_aq_error =  aq_buffer-now_aq;
           max_min_error =  max_data-min_data;
           if((now_aq_error>air_cal_point[2])&&(aq_level!=AQ_POL_LEV3))
           {
   
   
                if((max_min_error>air_cal_point[2]))
                {                                        
                      aq_level=AQ_POL_LEV3;
                }
                else if((max_min_error>air_cal_point[1])&&(aq_level!=AQ_POL_LEV2))
                {
                      if(aq_level==AQ_POL_LEV3)
                      {
                         if(now_aq_error>(air_cal_point[1]-AIR_POLLUTE_PASS))//?
                         {
                            //aq_low_point=temp;//save the old low point
                            aq_level=AQ_POL_LEV2;
                         }
                        else
                        {
                           //aq_low_point=temp;//save the old low point
                           aq_level=AQ_POL_LEV3;
                        }
                      }
                     else
                        aq_level=AQ_POL_LEV2;
                }
                else if((max_min_error>air_cal_point[0])&&(aq_level!=AQ_POL_LEV1))
                {
                      if(aq_level>AQ_POL_LEV1)
                      {
                            if(now_aq_error<(air_cal_point[0]-AIR_POLLUTE_PASS))
                               aq_level=AQ_POL_LEV1;
                           else
                              aq_level=AQ_POL_LEV2;
                      }
                     else
                        aq_level=AQ_POL_LEV1;
                }   
                
             
         }
         else if((now_aq_error>air_cal_point[1])&&(now_aq_error<air_cal_point[2])&&(aq_level!=AQ_POL_LEV2))
         {
            
             if(aq_level<AQ_POL_LEV2)
             {
                if(max_min_error>air_cal_point[1])
                {
                      if(aq_level==AQ_POL_LEV3)
                      {
                            if(now_aq_error<(air_cal_point[1]-AIR_POLLUTE_PASS))
                               aq_level=AQ_POL_LEV2;
                           else
                              aq_level=AQ_POL_LEV3;
                      }
                     else 
                           aq_level=AQ_POL_LEV2;
                }
                else if((max_min_error>air_cal_point[0])&&(aq_level!=AQ_POL_LEV1))   
                {
                      if(aq_level>AQ_POL_LEV1)
                      {
                            if(now_aq_error>(air_cal_point[0]-AIR_POLLUTE_PASS))
                               aq_level=AQ_POL_LEV1;
                           else
                              aq_level=AQ_POL_LEV2;
                      }
                     else
                           aq_level=AQ_POL_LEV1;
                }
             }
             else if(aq_level>AQ_POL_LEV2)
             {
                aq_level=AQ_POL_LEV2;
             }
         }   
         else if((now_aq_error>air_cal_point[0])&&(now_aq_error<air_cal_point[1])&&(aq_level!=AQ_POL_LEV1))   
         {
             if(aq_level<AQ_POL_LEV1)
             {
                 if(max_min_error>air_cal_point[0])
                {
                   if(aq_level>AQ_POL_LEV1)
                   {
                      if(now_aq_error>(air_cal_point[0]-AIR_POLLUTE_PASS))
                         aq_level=AQ_POL_LEV1;
                     else
                        aq_level=AQ_POL_LEV2;
                   }
                  else 
                     aq_level=AQ_POL_LEV1;
                 }
             }
             else if(aq_level>AQ_POL_LEV1)
             {
                aq_level=AQ_POL_LEV1;
             }
         }   
         else if(now_aq_error<(air_cal_point[0]-AIR_POLLUTE_PASS)||(aq_buffer<now_aq))
         {   
          
               aq_level=AQ_CLEAN_STATE;
            
         }

     }
     else if(k)                       //如果AQ值<实时AQ输入
     {
        aq_level=AQ_CLEAN_STATE;
         now_aq=aq_buffer;
     }
      

   
      
      if(aq_level<AQ_POL_LEV3)
      {

         air_up=0;
         
      }
      else   
      {
        
         air_up=1;
         
      }
     if(aq_buffer>now_aq)
     {
            now_aq_error =  aq_buffer-now_aq; 
            if(aq_level==AQ_CLEAN_STATE)
            {     
               show_aq_sen=100+((now_aq_error*100)/ air_cal_point[0]); 
 /*              
               if(show_aq_sen>=200)
                  show_aq_sen=199;
               else if(show_aq_sen<=99)
                  show_aq_sen=99;
*/               
            }
 /*            else if((aq_level>=AQ_POL_LEV1)&&(aq_level<=AQ_POL_LEV3))
            {
               if(now_aq_error>air_cal_point[aq_level-1])
                  show_aq_sen=200*aq_level+(((now_aq_error-air_cal_point[aq_level-1])/(air_cal_point[aq_level]-air_cal_point[aq_level-1]))*200);
            }   
  */        
            else if(aq_level==AQ_POL_LEV1)
            {
                
               show_aq_sen=200+(((now_aq_error-air_cal_point[0])/(air_cal_point[1]-air_cal_point[0]))*200);
//                if(show_aq_sen>=400)
//                  show_aq_sen=399;
//               else if(show_aq_sen<=200)
//                  show_aq_sen=200;
            
            }


            else if(aq_level==AQ_POL_LEV2)
            {
                
              if((now_aq_error>air_cal_point[2])&&(air_cal_point[2]>25) )
               show_aq_sen=400+(((now_aq_error-air_cal_point[1])/(air_cal_point[2]-air_cal_point[1]))*200);
//               if(show_aq_sen>=600)
//                  show_aq_sen=599;
//               else if(show_aq_sen<=400)
//                  show_aq_sen=400;
            
            }
            else if(aq_level==AQ_POL_LEV3)
            {
              
              if((now_aq_error>air_cal_point[3])&&(air_cal_point[3]>35) )
                  show_aq_sen=600+(((now_aq_error-air_cal_point[2])/(air_cal_point[3]-air_cal_point[2]))*200);
//                  if(show_aq_sen>=800)
//                     show_aq_sen=799;
//                  else if(show_aq_sen<=600)
//                     show_aq_sen=600;
            
            }
         
           //aq_level = 0,1,2,3
           aq_value = show_aq_sen+ aq_calibration;
           temp = (unsigned int)aq_level*200;
           if(aq_value>= temp+200)         //show_aq_sen = 99~199,200~399,400~599,600~799
                 aq_value = temp +199;
           else if(aq_value < temp)
                 aq_value = temp;
           if(aq_value<=99)
                  aq_value=99;
 
       }          
   }
   modbus.Aq = 	aq_value ;
   
}

uint16_t look_up_hummity_temp_table(uint16_t hum_temp, uint16_t tmper) 
{
   
   
   uint16_t rs=1;
   uint16_t vect[2][2];      
   uint16_t h_y1,h_y2;       
   uint16_t i,j;
              
   //0hummity ------100% hummity
   
   if(hum_temp<=hummity_talbe[1])   //<=65%,>65%
      j  =1;                        //<=65%
   else
      j = 2;                        //>65%
    
          
   for(i=1;i<5;i++)
   {
      if(tmper<=temperture_talbe[i])//<20C,20C~30C,30C~40C,40C~50C
      {
         vect[0][0]=temp_hummity_for_aq[i-1][j-1];   //select rs    //temperture_talbe[i-1]
         vect[0][1]=temp_hummity_for_aq[i-1][j];
         vect[1][0]=temp_hummity_for_aq[i][j-1];                    //temperture_talbe[i]
         vect[1][1]=temp_hummity_for_aq[i][j];
         
         h_y1 = vect[0][0]-((signed  int)hum_temp-hummity_talbe[j-1])*(vect[0][0]-vect[0][1])/(hummity_talbe[j] - hummity_talbe[j-1]);    //the rs of  temperture_talbe[i-1]    and hummidity
         h_y2 = vect[1][0]-((signed  int)hum_temp-hummity_talbe[j-1])*(vect[1][0]-vect[1][1])/(hummity_talbe[j] - hummity_talbe[j-1]);    //the rs of  temperture_talbe[i]    and hummidity
                      
         rs = h_y1 - (tmper - temperture_talbe[i-1])*(h_y1-h_y2)/(temperture_talbe[i]-temperture_talbe[i-1]);
         break;
      }         
   }          
    
      return rs;                
}



void Aq_Init(void)
{
		GPIO1_SetFieldValue(GPIO1_Ptr, AQ_CTR, 1); //turn on the lamp
}
