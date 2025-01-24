#include <stdio.h>
#include <string.h>

int main()
{
    char input1[100] = {0};
    char input2[100] = {0};
    int a[100] = {0}, b[100] = {0}, c[100] = {0};
    gets(input1);
    gets(input2);
    
    int lena = strlen(input1);
    int lenb = strlen(input2);
    int len = lena + lenb; // 不用再加1

    for (int i = lena - 1, j = 0 ; i >= 0; i--, j++)
    {
        a[j] = input1[i] - '0';
    }
    for (int i = lenb - 1, j = 0; i >= 0; i--, j++)
    {
        b[j] = input2[i] - '0';
    }

    for (int i = 0; i < lena; i++)
    {
        for (int j = 0; j < lenb; j++)
        {
            c[i + j] += a[i] * b[j]; // 注意+=号 以及c的下标（如果ij从1开始 下标要改成i+j-1）
        }
    }
    for (int i = 0; i < len; i++)
    {
        c[i + 1] += c[i] / 10; // +=  i+1
        c[i] %= 10;            // %=  i
    }

    while (!c[len - 1])
    {
        len--;
    }

    if (len >= 1) // 防止乘积为0
    {
        for (int i = len - 1; i >= 0; i--)
        {
            printf("%d", c[i]);
        }
    }
    else
    {
        printf("0");
    }
    return 0;
}