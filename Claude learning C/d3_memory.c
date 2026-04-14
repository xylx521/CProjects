#include <stdio.h>
#include <stdlib.h>

int global_var = 100;   //全局变量

void count_calls(){
    static int count = 0;  //静态局部变量
    count++;
    printf("调用次数：%d\n", count);
}

void stack_demo(void){
    int local = 42;
    printf("local 地址：%p\n", (void*)&local);
    printf("local 值：%d\n", local);
}  //local 在这里消失

void heap_demo(void){
    int *p = malloc(5 * sizeof(int));
    if(p == NULL){
        printf("malloc 失败\n");
        return;
    }
    for (int i = 0; i < 5; i++){
        p[i] = (i + 1) * 10;    //10 20 30 40 50
    }
    printf("堆上数据：");
    for (int i = 0; i < 5; i++){
        printf("%d ", p[i]);
    }
    printf("\n");

    free(p);   //释放内存
    p = NULL; //避免悬空指针
}

int main(void){
    printf("=== 全局变量示例 ===\n");
    printf("global_var 地址：%p, 值：%d\n", (void*)&global_var, global_var);

    printf("\n=== 静态局部变量示例 ===\n");
    count_calls();
    count_calls();
    count_calls();

    printf("\n=== 栈内存示例 ===\n");
    stack_demo();

    printf("\n=== 堆内存示例 ===\n");
    heap_demo();

    int x, y;
    int *pa = &x;
    int *pb = &y;
    printf("局部变量x的地址为:%p\n局部变量y的地址为:%p\n", (void*)pa, (void*)pb);
    printf("全局变量global_var的地址为:%p\n", (void*)&global_var);
    return 0;
}
