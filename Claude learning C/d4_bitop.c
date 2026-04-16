#include <stdio.h>
#include <stdint.h>

#define BIT(n)  (1U << (n))
#define SET_BIT(r, n)   ((r) |= BIT(n))
#define CLR_BIT(r, n)   ((r) &= ~BIT(n))
#define TGL_BIT(r, n)   ((r) ^= BIT(n))
#define GET_BIT(r, n)   (((r) >> (n)) & 1U)

void print_binary(uint8_t val){
    for(int i = 7; i >= 0; i--){
        printf("%d", GET_BIT(val , i));
        if (i == 4) printf(" ");
    }
    printf(" (0x%02X)\n", val);
}

uint8_t set_bits(uint8_t reg, uint8_t start, uint8_t len, uint8_t val){
    uint8_t mask = ((1U << len) - 1) << start;  //生成掩码
    reg &= ~mask;  //清除目标位
    reg |= (val << start) & mask;  //设置新值
    return reg;
}

int main(void){
    uint8_t reg = 0x00;  //8位寄存器初始值

    printf("初始值: ");
    print_binary(reg);

    SET_BIT(reg, 3);  //设置第3位
    printf("置位 bit3: ");
    print_binary(reg);

    SET_BIT(reg, 7);
    printf("置位 bit7: ");
    print_binary(reg);

    CLR_BIT(reg, 3);  //清除第3位
    printf("清除 bit3: ");
    print_binary(reg);

    TGL_BIT(reg, 7);  //翻转第7位
    printf("再翻转:    ");
    print_binary(reg);

    printf("\nbit7 当前值: %d\n", GET_BIT(reg, 7));

    print_binary(set_bits(0x00, 2, 3, 0b101));

    return 0;
}

