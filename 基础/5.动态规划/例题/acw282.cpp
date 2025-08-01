// 区间dp问题

// 总结一下闫氏dp思路，和之前学的差不多。dp还是取决于刷题量。
// 一、 状态表示 f(i,j)
// 1. 集合：f(i,j)的含义，需要自己抽象
// 2. 属性：f(i,j)的值代表什么，一般与题目相同
// 二、 状态计算
// 将f(i,j)拆分成更小的子问题，找到状态转移方程
// 这里方法与之前相同：先找到最后一步

// 本题为区间dp，f(i,j)集合定义为从i到j区间合并的方案，属性看题目：最小代价

#include <iostream>
#include <algorithm>

using namespace std;

const int N = 310;

int n;
int s[N];
int f[N][N];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        s[i] += s[i - 1];
    }

    for (int len = 2; len <= n; len++) // 枚举长度
        for (int i = 1; i + len - 1 <= n; i++) // 枚举左端点
        {
            int j = i + len - 1; // 右端点
            f[i][j] = 1e9; // 初始化为一个很大的数
            for (int k = i; k < j; k++) // 枚举分割点
                f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j] + s[j] - s[i - 1]);
        }
    
    cout << f[1][n] << endl; // 输出最小代价
    return 0;
}