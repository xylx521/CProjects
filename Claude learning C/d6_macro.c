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

    
}