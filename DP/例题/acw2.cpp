// 1. dfs + 记忆化搜索
#include <iostream>
#include <algorithm>
#include <vector>
#define MAXN 1010
using namespace std;

int n, m;
vector<int> v(MAXN, 0);
vector<int> w(MAXN, 0);
// 二维数组 回想bfs中对多维数组的讲解。多维数组是一个多参数映射的数据结构，因此可以简单视为多元函数
vector<vector<int>> mem(MAXN, vector<int>(MAXN, 0));

int dfs(int x, int restV)
{
    if (mem[x][restV])
        return mem[x][restV];
    if (x > n)
        return 0;

    int sum = 0;
    if (restV >= v[x]) // 可以选
        sum = max(dfs(x + 1, restV), dfs(x + 1, restV - v[x]) + w[x]);
    else // 不能选
        sum = dfs(x + 1, restV);

    mem[x][restV] = sum;
    return sum;
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> v[i] >> w[i];
    cout << dfs(1, m);
    return 0;
}


// 2.顺序递推
#include <iostream>
#include <algorithm>
#include <vector>
#define MAXN 1010
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> v(MAXN, 0);
    vector<int> w(MAXN, 0);
    vector<vector<int>> dp(MAXN, vector<int>(MAXN, 0));

    // 输入每个物品的体积和价值
    for (int i = 1; i <= n; i++)
        cin >> v[i] >> w[i];

    // 递推求解
    for (int i = 1; i <= n; i++) // 遍历每个物品
    {
        for (int j = 0; j <= m; j++) // 遍历背包容量
        {
            // 不选第i个物品。直接继承上一个状态（暂时初始化）
            dp[i][j] = dp[i - 1][j];
            if (j >= v[i]) // 状态转移方程，反过来了
                // 若当前背包容量能装下第 i 个物品，考虑选该物品的情况
                dp[i][j] = max(dp[i][j], dp[i - 1][j - v[i]] + w[i]);
        }
    }

    cout << dp[n][m] << endl; // 顺序递推，出口、公式、起点都相反
    return 0;
}