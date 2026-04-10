#include <stdio.h>

void add_one(int *p){
    *p = *p + 1;
}

int main(void){
    int x = 10;
    int y = 20;
    int *pa = &x;
    int *pb = &y;

    //任务1：打印 x 和 y 的地址，观察地址差值是多少？
    printf("x 的地址是：%p\n", (void *)&x);
    printf("y 的地址是：%p\n", (void *)&y);

    //任务2：通过指针交换 x 和 y 的值（不能用 x=、y=直接赋值）
    int temp = *pa;
    *pa = *pb;
    *pb = temp;
    printf("交换后 x=%d, y=%d\n", x, y);

    //任务3：调用函数，通过指针修改 x 的值
    add_one(&x);
    printf("add_one后 x=%d\n", x);

    return 0;
}