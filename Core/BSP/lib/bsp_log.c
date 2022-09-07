#include "bsp_log.h"

void BSP_Log_Init() { 
    SEGGER_RTT_Init();
}

int printf_log(const char* fmt, ...) {
    // char buffer[128];
    va_list args;
    va_start(args, fmt);
    // int n = vsnprintf(buffer,sizeof(buffer),fmt,args);
    // SEGGER_RTT_Write(BUFFER_INDEX,buffer,n);
    int n = SEGGER_RTT_vprintf(BUFFER_INDEX, fmt, &args);
    va_end(args);
    return n;
}

void Float2Str(char *str, float va) {
    uint8_t flag = va < 0;
    uint32_t head = (int)fabs(va);
    int point = (int)((va - head) * 1000);
    head = abs(head);
    point = abs(point);
    if (point == 0) {
        if (flag)
            sprintf(str, "-%lu\n", head);
        else
            sprintf(str, " %lu\n", head);
    } else {
        if (flag)
            sprintf(str, "-%lu.%d\n", head, point);
        else
            sprintf(str, " %lu.%d\n", head, point);
    }
}