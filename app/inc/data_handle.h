#ifndef __DATA_HANDLE_H__
#define __DATA_HANDLE_H__

#include "stm32f10x.h"

#define TRUE                     0x01
#define FALSE                    0x00

#define FRAME_HEADER_FIELD       0x00
#define DEVICE_ADDR_FIELD        0x01
#define CMD_FIELD                0x02

#define PROTOCOL_MINIMUM_LENGTH  0x05

// device addr
#define LEFT_POWER_ADDR          0x22
#define RIGHT_POWER_ADDR         0x28

// cmd



// lamp state
#define LAMP_OFF                 0x00
#define LAMP_ON_FIRST            0x01
#define LAMP_ON_READY            0x02
#define LAMP_ON                  0x03



void frame_data_prase(void);
uint8_t get_check_sum(uint8_t *pack, uint8_t pack_len);
void data_handle(void);
void lp_amd_handle(void);
void rp_amd_handle(void);
void send_ack(uint8_t *data, uint8_t length);
void c2_cmd_handle(void);
void c2_cmd_handle_rp(void);

#endif

