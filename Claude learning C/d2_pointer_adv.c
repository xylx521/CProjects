#include <stdio.h>

//任务1：用指针遍历数组，求和
int array_sum(int *arr, int len){
    int sum = 0;
    //要求：只能用指针运算（*(arr+i)），不能用arr[i]
    for(int i = 0; i < len; i++){
        sum += *(arr + i);
    }
    return sum;
}

//任务2：函数指针实现简易计算器
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
int div(int a, int b) {
    if(b == 0){
        printf("错误:除数不能为0\n");
        return 0;
    } // 简单错误处理，实际使用时应更完善
    return a / b; 
}

typedef int (*CalcFunc)(int, int);

int calculate(CalcFunc op, int a, int b){
    return op(a, b);
}

int main(void){
    //任务1测试
    int nums[6] = {3, 1, 4, 1, 5, 9};
    printf("数组求和 = %d\n", array_sum(nums, 6));

    //任务2测试
    CalcFunc ops[4] = {add, sub , mul, div};
    const char *names[4] = {"加", "减", "乘", "除"};

    for(int i = 0; i < 4; i++){
        printf("10 %s 3 = %d\n", names[i], calculate(ops[i], 10, 3));
    }

    calculate(div, 10, 0); // 注意：除法测试会导致运行时错误，实际使用时应添加检查避免除以零


    return 0;
}