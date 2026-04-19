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

}
