#ifndef _BSP_LOG_H
#define _BSP_LOG_H

#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"
#include "bsp_def.h"
#include "stdio.h"
#include "math.h"

void BSP_Log_Init();
int printf_log(const char* fmt, ...);
void Float2Str(char* str, float va);
#endif