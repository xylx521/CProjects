#include <stdio.h>
#include <stdint.h>
#include "d6_sensor.h"


// static inline 代替函数式宏
static inline float clamp(float val, float min, float max){
    if (val < min) return min;
    if (val > max) return max;
    return val;
}

//模拟读取传感器
SensorData_t read_sensor(float raw_temp){
    SensorData_t data;

    LOG("原始数据 = %.2f", raw_temp);

    if (!TEMP_VALID(raw_temp)) {
        LOG("温度超出范围！");
        data.temperature = clamp(raw_temp, TEMP_MIN, TEMP_MAX);
        data.status = SENSOR_ERROR;
    } 
    else {
        data.temperature = raw_temp;
        data.status = SENSOR_OK;
    }
    return data;
}

int main(void){
    //测试1：正常数据
    SensorData_t d1 = read_sensor(25.6f);
    printf("温度=%.2f 状态=%d\n\n", d1.temperature, d1.status);

    //测试2：超出范围的数据
    SensorData_t d2 = read_sensor(200.0f);
    printf("温度=%.2f 状态=%d\n", d2.temperature, d2.status);

    //测试3：打印编译信息
    printf("编译时间: %s %s\n", __DATE__, __TIME__);
    printf("最大传感器数量: %d\n", SENSOR_MAX_COUNT);
    printf("MCU寄存器类型: %d字节\n", (sizeof(reg_t)));
    return 0;
}