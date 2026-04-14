#include <stdio.h>

void add_one(int *p){
    *p = *p + 1;
}

//运行成功后，额外挑战：把 add_one 改成 add_n(int *p, int n)，让它加任意数。
void add_n(int *p, int n) {
    *p = *p + n;
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

    //运行成功后，额外挑战：把 add_one 改成 add_n(int *p, int n)，让它加任意数。
    int n1 = 5;
    add_n(&x, n1);
    printf("x 加 %d 后 x=%d\n", n1, x);

    return 0; 
}


