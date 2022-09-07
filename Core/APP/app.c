#include "app.h"

uint32_t adcsensor_depth;
uint32_t Get_ADC_Depth(ADC_HandleTypeDef *hadc);

void Float2Str(char *str, float va);

void APP_Layer_Init() {
    // create
}

void APP_Loop() {
    // update
    adcsensor_depth = Get_ADC_Depth(&hadc1);
    char *strdepth = (char *)malloc(5);
    Float2Str((char *)strdepth, (float)adcsensor_depth);
    char sendf[6] = "fuck\n";
    char *sendframe = sendf;
    BSP_UART_Send_queue(0, (uint8_t *)sendframe, 6);
    // bsp_delay
    BSP_UART_Send_queue(0, (uint8_t *)strdepth, 5);
    free(strdepth);
}

// 打印输出等到ozone的窗口 用于测试项目
void APP_Log_Loop() {}

void APP_Layer_default_loop() {
}

uint32_t Get_ADC_Depth(ADC_HandleTypeDef *hadc) {
    static uint32_t depth;
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
    // srart ADC1
    HAL_ADC_Start(hadc);
    //等待ADC转换完成，超时为100ms
    HAL_ADC_PollForConversion(hadc, 100);
    //判断ADC是否转换成功
    if (HAL_IS_BIT_SET(HAL_ADC_GetState(hadc), HAL_ADC_STATE_REG_EOC)) {
        // read adc1
        depth = HAL_ADC_GetValue(hadc);
    }
    return depth;
}

void Float2Str(char *str, float va) {
    int flag = va < 0;
    int64_t head = (int)va;
    int point = (int)((va - head) * 1000);
    head = abs(head);
    point = abs(point);
    if (point == 0) {
        if (flag)
            sprintf(str, "-%ld \n", head);
        else
            sprintf(str, "%ld \n", head);
    } else {
        if (flag)
            sprintf(str, "-%ld.%d \n", head, point);
        else
            sprintf(str, "%ld.%d \n", head, point);
    }
}