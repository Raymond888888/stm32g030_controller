#ifndef _PC_COM_H
#define _PC_COM_H
#include "hal.h"

typedef struct pc_com
{
    uint8_t start;
    uint8_t* data;
    uint8_t end;
}pc_com_data;


uint8_t* PC_data_receive();
#endif 