#include <stdio.h>

int main(){
int a = 0x12345678;
char *p = (char *)a;
printf("指针p的值是：%p\n", p);
}
