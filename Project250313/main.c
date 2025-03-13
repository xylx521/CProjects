#include <stdio.h>
#include <stdlib.h>

int main() {
    int a = 10; 
    int arr1[10] = {0};
    printf("arr1[0] = %d\na = %d\n", arr1[0], a);
    printf("请输入arr1[0]的值: ");
    scanf("%d", &arr1[0]);
    printf("arr1[0] = %d\n", arr1[0]);
    return 0;
}
