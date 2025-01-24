#include <stdio.h>
#include <string.h>
#include <math.h>

void trans(char *num, int len, int *numInt)
{
    for (int i = len - 1, j = 0; i >= 0; i--, j++)
    {
        if (num[i] >= '0' && num[i] <= '9')
            numInt[j] = num[i] - '0';
        else
        {
            if (num[i] >= 'a' && num[i] <= 'f')
                numInt[j] = num[i] - ('a' - 'A') - 'A' + 10; // 搞清楚自己要做什么（左式的类型！）
            if (num[i] >= 'A' && num[i] <= 'F')
                numInt[j] = num[i] - 'A' + 10;
        }
    }
}

int main()
{
    char arr[400] = {0};
    gets(arr);
    char num1[200] = {0};
    char num2[200] = {0};
    int len = strlen(arr);
    int record = 0;
    for (int i = 0; i < len; i++)
    {
        if (arr[i] == '+') // 以后赋值倒过来写 debug真的太难找了
        {
            record = i;
            break;
        }
        num1[i] = arr[i];
    }
    for (int i = record + 1, j = 0; i < len; i++, j++)
    {
        if (arr[i] == '=')
            break;
        num2[j] = arr[i];
    }

    int len1 = strlen(num1);
    int len2 = strlen(num2);
    len = fmax(len1, len2) + 1; // 模板

    int num1Int[200] = {0};
    int num2Int[200] = {0};
    int ansInt[200] = {0};

    trans(num1, len1, num1Int);
    trans(num2, len2, num2Int);
    // 这里是高精度乘法的写法 很蠢
    for (int i = 0; i < len; i++)
        ansInt[i] = num1Int[i] + num2Int[i];
    for (int i = 0; i < len; i++)
    {
        ansInt[i + 1] += ansInt[i] / 16; // +=
        ansInt[i] %= 16;                 // %=
    }
    // 去前导0 模板
    while (ansInt[len - 1] == 0)
        len--;

    printf("0X");
    for (int i = len - 1; i >= 0; i--)
        ansInt[i] >= 10 ? printf("%c", ansInt[i] - 10 + 'A') : printf("%d", ansInt[i]);
    return 0;
}