#include <stdio.h>
#include <stdint.h>

// === 任务1：按键回调 ====
typedef void (*ButtonCallback)(void);
ButtonCallback g_callback = NULL;

void button_register(ButtonCallback cb) {
    g_callback = cb;
}

void button_trigger(void) {
    if (g_callback != NULL) {
        g_callback();
    }
    else {
        printf("没有注册回调函数\n");
    }
}


void action_led_toggle(void) { printf("LED 翻转\n");}
void action_beep(void)       {printf("蜂鸣器响\n");}

// === 任务2：状态机 ===
typedef enum {
    STATE_IDLE = 0,
    STATE_COLLECT,
    STATE_TRANSMIT,
    STATE_MAX
} State_t;

void do_idle(void)      {printf("[空闲] 等待...\n");}
void do_collect(void)   {printf("[采集] 读取传感器\n");}
void do_transmit(void)  {printf("[发送] 上传数据\n");}

typedef void (*StateFunc)(void);
StateFunc state_table[STATE_MAX] = {do_idle, do_collect, do_transmit};

// === 任务3：驱动注册 ====
typedef struct {
    const char *name;
    void (*init)(void);
    void (*read)(void);
}   Driver_t;

void  sensor_a_init(void) { printf("传感器A初始化\n");}
float sensor_a_read(void) { return 23.5f; }

void  sensor_b_init(void) { printf("传感器B初始化\n");}
float sensor_b_read(void) { return 31.2f; }

void app_run(Driver_t *drv) {
    printf("运行驱动: %s\n", drv->name);
    drv->init();
    printf("读取值: %.1f\n\n", drv->read());
}

int main(void) {
    //部分1：按键回调
    printf("=== 按键回调 ===\n");
    button_register(action_led_toggle);
    button_trigger();
    button_register(action_beep);
    button_trigger();

    //部分2：状态机
    printf("\n=== 状态机 ===\n");
    for (int i = 0; i < STATE_MAX; i++) {
        printf("状态 %d: ", i);
        state_table[i]();
    }

    //部分3：驱动注册
    printf("\n=== 驱动注册 ===\n");
    Driver_t sensor_a = {"传感器A", sensor_a_init, sensor_a_read};
    Driver_t sensor_b = {"传感器B", sensor_b_init, sensor_b_read};
    app_run(&sensor_a);
    app_run(&sensor_b);

    return 0;
}