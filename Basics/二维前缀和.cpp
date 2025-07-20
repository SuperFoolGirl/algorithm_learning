// 前缀和算法，下标都从1开始
// 计算内容：左上角为x1，y1，右下角为x2，y2的矩形区域的和
// 计算差值公式：res = sum[x2][y2] - sum[x1-1][y2] - sum[x2][y1-1] + sum[x1-1][y1-1]
// 前缀和计算公式：sum[i][j] = arr[i][j] + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1]
// 两公式符号是相反的

#include <iostream>

using namespace std;

int sum[3][3];

int main()
{
    int arr[4][4] = {
        {0, 0, 0, 0},
        {0, 1, 1, 1},
        {0, 1, 1, 1},
        {0, 1, 1, 1}}; // 预留了最外层的0行0列，方便计算

    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= 3; j++)
            sum[i][j] = arr[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1]; // 前缀和公式
}