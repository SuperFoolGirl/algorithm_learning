#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // 左右是列变换 上下是行变换
    int idx = 0;
    int map[100][100] = {0};
    int x = 1, y = 1;
    for (int i = 1; i <= n * n; i++)
    {
        map[x][y] = i; // 先写 然后判断下一步是否合法

        if (x + dir[idx][0] < 1 || x + dir[idx][0] > n || y + dir[idx][1] < 1 || y + dir[idx][1] > n || map[x + dir[idx][0]][y + dir[idx][1]]) // 最后一个容易忽略：已经填过的位置不能再填
            idx = (idx + 1) % 4; // 这样写比较方便

        x += dir[idx][0];
        y += dir[idx][1];
    }

    // 考试输入
    int lineCnt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (lineCnt)
            puts("");
        lineCnt++;
        int cnt = 0;
        for (int j = 1; j <= n; j++)
        {
            if (cnt)
                printf(" ");
            cnt++;
            printf("%-2d", map[i][j]);
        }
    }
    return 0;
}