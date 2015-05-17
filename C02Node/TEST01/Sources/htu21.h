#ifndef _HTU21_H
#define _HTU21_H

#include "IO_Map.h"


#define   CMD_READ_PARAMS            0xc1
#define   CMD_READ_VERSION         0xc2
#define   CMD_OVERRIDE_CAL         0xd3
#define   CMD_READ_CAL_PT            0xd4
#define   CMD_HEATING_CONTROL         0xd5
#define   CMD_CLEAR_TABLE            0xe4
#define   CMD_TEMP_CAL            0xe5
#define   CMD_HUM_CAL               0xe6
#define   CMD_SN_WRITE              0xee
#define   CMD_SN_READ               0xef



#define CMD_TRIGGER_TEMP_HOLD_MASTER    0xe3
#define CMD_TRIGGER_HUM_HOLD_MASTER     0xe5
#define CMD_TRIGGER_TEMP_NO_HOLD_MASTER 0xf3
#define CMD_TRIGGER_HUM_NO_HOLD_MASTER  0xf5
#define CMD_WRITE_USER_REGISTER         0xe6
#define CMD_READ_USER_REGISTER          0xe7
#define CMD_SOFT_RESET                  0xfe

#define SELECT_TEMP                 0x00
#define SELECT_HUM                  0x02

#define TRIGGER_HUM                 0x00
#define READ_HUM                    0x01
#define TRIGGER_TEMP                0x02
#define READ_TEMP                   0x03

// HTU21D definations
#define DEV_ADDR     0x80
#define I2C_WR       0x00
#define I2C_RD       0x01



uint8_t htu21d_write_user_register(uint8_t bit_index, uint8_t bit_value);
uint8_t htu21d_soft_reset(void);
uint8_t htu21d_trigger_measurement_no_hold_master(uint8_t type);
uint8_t htu21d_read_measurement_no_hold_master(uint8_t type, uint16_t *value);
uint8_t htu21d_calculation(uint8_t type, uint16_t src, int16_t *dst);
void HTU21_TASK(void);
unsigned int Hum_Cal_Roution(uint16_t Hum_Buf) ;
//void Insert_Cal_Point(unsigned int Sensor_value, unsigned int Meter_value );
//void store_hum_calibration_data(void) ;
void Clear_hum_table(void) ;



















#endif
