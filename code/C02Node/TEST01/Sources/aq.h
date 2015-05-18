#ifndef _AQ_H_
#define _AQ_H_ 

#include "IO_Map.h"










#define INIT_AQ 0
#define AQ_CHECK 1
#define NO_AQ_CHECK 2
#define AQ_TIME  150 //five mins
#define AQ_UP_TIME 600 //20 mins
#define AIR_POLLUTE_PASS 5
#define AQ_CLEAN_STATE 0
#define AQ_POL_LEV1 1
#define AQ_POL_LEV2 2
#define AQ_POL_LEV3 3 

#define alarm_delay 20 


 
void check_Air_Quality(void);
void Aq_Init(void) ;

extern uint16_t   aq_analog_input  ; 
extern uint16_t  aq_value ;


#endif
