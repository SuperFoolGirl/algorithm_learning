#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define maxn 100
int a[10] = {0}, ans = 0;
int b1[maxn] = {0}, b2[maxn] = {0}, b3[maxn] = {0};
int ansArr[maxn][10] = {0};
bool repeat[maxn] = {0};

void dfs(int x)
{
    if (x > 8)
    {
        ans++;
        memcpy(ansArr[ans], a, sizeof(a));
        return;
    }

    for (int i = 1; i <= 8; i++)
    {
        if (b1[i] == 0 && b2[x + i] == 0 && b3[x - i + 15] == 0)
        {
            a[x] = i;
            b1[i] = b2[x + i] = b3[x - i + 15] = 1;
            dfs(x + 1);
            b1[i] = b2[x + i] = b3[x - i + 15] = 0;
        }
    }
}

int cmp(const void *a, const void *b)
{
    return memcmp((int *)a, (int *)b, sizeof(int) * 9);
}

bool up_down_judge(int i, int j)
{
    for (int k = 1; k <= 8; k++)
    {
        if (ansArr[j][k] != 9 - ansArr[i][k])
        {
            return false;
        }
    }
    return true;
}

bool left_right_judge(int i, int j)
{
    for (int k = 1; k <= 4; k++)
    {
        if (ansArr[i][k] != ansArr[j][9 - k])
        {
            return false;
        }
    }
    return true;
}

bool vice_line(int i, int j)
{
    for (int k = 1; k <= 8; k++)
    {
        int xi = ansArr[i][k], yi = k;
        int xj = 9 - yi, yj = 9 - xi;
        if (ansArr[j][yj] != xj)
        {
            return false;
        }
    }
    return true;
}

bool main_line(int i, int j)
{
    for (int k = 1; k <= 8; k++)
    {
        int xi = ansArr[i][k], yi = k;
        int xj = yi, yj = xi;
        if (ansArr[j][yj] != xj)
        {
            return false;
        }
    }
    return true;
}

bool rotate1(int i, int j)
{
    for (int k = 1; k <= 8; k++)
    {
        int xi = ansArr[i][k], yi = k;
        int xj = yi, yj = 9 - xi;
        if (ansArr[j][yj] != xj)
        {
            return false;
        }
    }
    return true;
}

bool rotate2(int i, int j)
{
    for (int k = 1; k <= 8; k++)
    {
        int xi = ansArr[i][k], yi = k;
        int xj = 9 - xi, yj = 9 - yi;
        if (ansArr[j][yj] != xj)
        {
            return false;
        }
    }
    return true;
}

bool rotate3(int i, int j)
{
    for (int k = 1; k <= 8; k++)
    {
        int xi = ansArr[i][k], yi = k;
        int xj = 9 - yi, yj = xi;
        if (ansArr[j][yj] != xj)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    dfs(1);
    qsort(ansArr + 1, ans, sizeof(ansArr[1]), cmp);
    for (int i = 1; i < ans; i++)
    {
        for (int j = i + 1; j <= ans; j++)
        {
            if (up_down_judge(i, j))
            {
                repeat[j] = 1;
                continue;
            }
            if (left_right_judge(i, j))
            {
                repeat[j] = 1;
                continue;
            }
            if (main_line(i, j))
            {
                repeat[j] = 1;
                continue;
            }
            if (vice_line(i, j))
            {
                repeat[j] = 1;
                continue;
            }
            if (rotate1(i, j)) // 顺时针90
            {
                repeat[j] = 1;
                continue;
            }
            if (rotate2(i, j)) // 顺时针180
            {
                repeat[j] = 1;
                continue;
            }
            if (rotate3(i, j)) // 顺时针270
            {
                repeat[j] = 1;
                continue;
            }
        }
    }
    int cnt = 0;
    for (int i = 1; i <= ans; i++)
    {
        if (repeat[i])
        {
            continue;
        }
        printf("No%d:", ++cnt);
        for (int j = 1; j <= 8; j++)
        {
            printf("%d ", ansArr[i][j]);
        }
        puts("");
    }
    return 0;
}