

#ifndef	__OS_H__

#define	__OS_H__


#define	OS_TICK					10 // 1 * 10 = 10ms

typedef enum
{
	TASK_OUTPUT = 0,	 //10
	TASK_HUM, //100
	TASK_AQ,		//100
	TASK_RTD,		     //100	
	TASK_FLASH ,
	TASK_CO2 ,
	TASK_END
} tpye_task;

void task_init(void);
void task_manage(void);


#endif
