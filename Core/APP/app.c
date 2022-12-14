#include "app.h"

uint32_t adcsensor_depth;
uint32_t Get_ADC_Depth(ADC_HandleTypeDef *hadc);
void Senddepth_test();

void APP_Layer_Init() {
    // create
}

void APP_Loop() {
    // update
    adcsensor_depth = Get_ADC_Depth(&hadc1);
    // Senddepth_test();
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

void Senddepth_test(){
    char *strdepth = (char *)malloc(24*sizeof(char));
    Float2Str((char *)strdepth, adcsensor_depth);
    char sendf[6] = "fuck\n";
    uint8_t *sendp = (uint8_t*)malloc(12*sizeof(uint8_t));
    memcpy(sendp,strdepth,6*sizeof(char));
    memcpy(sendp+6,sendf,6*sizeof(char));
    BSP_UART_Send_queue(0, (uint8_t *)sendp, 12);
    bsp_delay_us(10);
    free(strdepth);
    free(sendp); 
}



// s
// t
// high_angle
// low_angle
// distance
// d
// e
