#include <stdio.h>
#include <string.h>
#include <math.h>

int main()
{
    char input1[100] = {0};
    char input2[100] = {0};
    gets(input1);
    gets(input2);
    int a[100] = {0};
    int b[100] = {0};
    int c[100] = {0};
    
    int len = fmax(strlen(input1), strlen(input2)); // 去前导0的话要+1

    for (int i = strlen(input1) - 1, j = 0; i >= 0; i--, j++)
    {
        a[j] = input1[i] - '0';
    }
    for (int i = strlen(input2) - 1, j = 0; i >= 0; i--, j++)
    {
        b[j] = input2[i] - '0';
    }

    // 这里提供了三步写法 16进制那个题提供了两步写法
    for (int i = 0; i < len; i++)
    {
        c[i] += a[i] + b[i];   // +=  i
        c[i + 1] = c[i] / 10;  // =   i+1
        c[i] %= 10;            // %=  i
    }

    // 加法不是消前导0 而是看最高位是否需要增添 当然用while去前导0也可
    if (c[len])
    {
        len++;
    }

    for (int i = len - 1; i >= 0; i--) // i初始化别错了
    {
        printf("%d", c[i]);
    }
    return 0;
}