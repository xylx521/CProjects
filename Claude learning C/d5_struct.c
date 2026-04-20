#include <stdio.h>
#include <stdint.h>

// ====== 结构体对齐实验 ====
typedef struct {
    uint8_t a;
    uint32_t b;
    uint8_t c;   
} Bad_t;

typedef struct {
    uint32_t b;
    uint8_t a;
    uint8_t c;
} Good_t;

// ====== 部分2：联合体大小端实验======
typedef union {
    uint32_t word;
    uint8_t bytes[4];
} U32_t;

// ====== 部分3：枚举 + 状态机======
typedef enum {
    LED_OFF = 0,
    LED_ON,
    LED_BLINK,
    LED_STATE_MAX
} LedState_t;

void led_off(void) {printf("LED 关闭\n");}
void led_on(void) {printf("LED 点亮\n");}
void led_blink(void) {printf("LED 闪烁\n");}

typedef void (*LedHandler)(void);
LedHandler led_handlers[LED_STATE_MAX] = {
    led_off,
    led_on,
    led_blink,
};

// 传感器类型
typedef enum {
    SENSOR_TEMP  = 0,
    SENSOR_HUMID = 1,
    SENSOR_PRESS = 2,
} SensorType_t;

// 传感器数据（union 节省内存，同一时刻只有一种数据）
typedef union {
    float    temperature;
    float    humidity;
    uint32_t pressure;
} SensorValue_t;

// 传感器完整描述
typedef struct {
    SensorType_t  type;     // 传感器类型
    SensorValue_t value;    // 当前值
    uint8_t       valid;    // 数据是否有效
    uint32_t      last_update_ms;  // 上次更新时间
} Sensor_t;

void print_sensor(Sensor_t *s) {
    switch ((*s).type) {
        case SENSOR_TEMP:
            printf("温度: %.2f °C\n", (*s).value.temperature);
            break;
        case SENSOR_HUMID:
            printf("湿度: %.2f %%\n", (*s).value.humidity);
            break;
        case SENSOR_PRESS:
            printf("压力: %u hPa\n", (*s).value.pressure);
            break;
    }
    switch(s->valid) {
        case 0: printf("数据无效\n"); break;
    }
}

int main(void) {
    //部分1：结构体对齐
    printf("=== 内存对齐 ===\n");
    printf("Bad_t 大小: %zu 字节\n", sizeof(Bad_t));
    printf("Good_t 大小： %zu 字节\n", sizeof(Good_t));

    //部分2：联合体大小端
    printf("\n=== 联合体大小端 ===\n");
    U32_t u;
    u.word = 0x12345678;
    printf("word = ox%08X\n", u.word);
    for (int i = 0; i < 4; i++) {
        printf("byte[%d] = 0x%02X\n", i, u.bytes[i]);
    }
    //观察：bytes[0] 是 高字节还是低字节？系统是小端还是大端？

    //部分3：枚举 + 状态机
    printf("\n=== 状态机 ===\n");
    LedState_t state = LED_OFF;
    for (int i = 0; i < LED_STATE_MAX; i++) {
        state = (LedState_t)i;
        printf("状态 %d: ", state);
        led_handlers[state]();
    }

    //部分4：传感器结构体
    printf("\n=== 传感器结构体 ===\n");
    Sensor_t sensor = {
        .type = SENSOR_TEMP,
        .value.temperature = 25.0,
        .valid = 1,
        .last_update_ms = 1000,
    };
    Sensor_t sensor2 = {
        .type = SENSOR_HUMID,
        .value.humidity = 50.0,
        .valid = 1,
        .last_update_ms = 2000,
    };
    Sensor_t sensor3 = {
        .type = SENSOR_PRESS,
        .value.pressure = 1000,
        .valid = 1,
        .last_update_ms = 3000,
    };
    Sensor_t sensorerr = {
        .type = SENSOR_TEMP,
        .value.temperature = 25.0,
        .valid = 0,
        .last_update_ms = 1000,
    };
    Sensor_t sensors[] = {sensor, sensor2, sensor3, sensorerr};
    for (int i = 0; i < sizeof(sensors) / sizeof(sensors[0]); i++) {
        print_sensor(&sensors[i]);
    }
    return 0;
}
