#ifndef D6_SENSOR_H
#define D6_SENSOR_H

#include <stdint.h>

//配置宏
#define SENSOR_MAX_COUNT 4
#define TEMP_MIN        -40.0f
#define TEMP_MAX         85.0f

//调试开关（注释掉则关闭所有日志）
#define DEBUG

#ifdef DEBUG
    #define LOG(fmt, ...) \
        printf("[%s:%d] " fmt "\n", __func__, __LINE__, ##__VA_ARGS__)
#else
    #define LOG(fmt, ...)
#endif

//范围检查宏
#define TEMP_VALID(t)  ((t) >= TEMP_MIN && (t) <= TEMP_MAX)

//传感器状态
typedef enum {
    SENSOR_OK    = 0,
    SENSOR_ERROR = 1,
} SensorState_t;

//传感器数据
typedef struct {
    float         temperature;
    SensorState_t status;
} SensorData_t;

#endif

