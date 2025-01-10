#include <stdio.h>

int main()
{
    int arr[105][105] = {0};
    int n;
    scanf("%d", &n);
    int idx = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            arr[j][i] = (idx++) % 10;
        }
    }
    int lineCnt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (lineCnt) // 这个模型必须写在前面！
            puts("");
        lineCnt++;
        for (int k = 1; k < i; k++)
        {
            printf("  ");
        }
        for (int j = i; j <= n; j++)
            printf(" %d", arr[i][j]); // 题目要求每位数字占两位
    }
    return 0;
}