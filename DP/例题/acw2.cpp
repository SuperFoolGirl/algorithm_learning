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
vector<vector<int>> mem(MAXN, vector<int>(MAXN, 0)); // mem[i][j]表示i个物品，背包容量为j 后的最大价值

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
    vector<vector<int>> dp(MAXN, vector<int>(MAXN, 0)); // dp[i][j]表示前i个物品，背包容量为j时的最大价值。意义与mem互补

    // 输入每个物品的体积和价值
    for (int i = 1; i <= n; i++)
        cin >> v[i] >> w[i];

    // 基准情况已经隐性地给出了：dp[0][j] = 0
    // 由于dp是二维数组，因此递推循环是两层
    for (int i = 1; i <= n; i++) // 遍历每个物品
    {
        for (int j = 0; j <= m; j++) // 遍历背包容量
        {
            if (j >= v[i]) // 状态转移方程，反过来了
                // 若当前背包容量能装下第 i 个物品，考虑选该物品的情况
                dp[i][j] = max(dp[i][j], dp[i - 1][j - v[i]] + w[i]);
            else
                // 若当前背包容量不能装下第 i 个物品，只能不选
                dp[i][j] = dp[i - 1][j];
        }
    }

    cout << dp[n][m] << endl; // 表示考虑所有 n 个物品，背包容量为 m 时能获得的最大价值，将其输出。回顾上方的循环，第n个物品不一定选，但不妨碍dp状态的标记
    return 0;
}


// 3.逆序递推
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

    for (int i = 1; i <= n; i++)
        cin >> v[i] >> w[i];

    for (int i = n; i >= 1; i--) // 逆序遍历每个物品
    {
        for (int j = 0; j <= m; j++) // 正序遍历背包容量
        {
            if (j >= v[i])
                dp[i][j] = max(dp[i][j], dp[i + 1][j - v[i]] + w[i]); // dp数组初始化为0了，不用担心越界
            else
                dp[i][j] = dp[i + 1][j];
        }
    }

    cout << dp[1][m] << endl; // 递归搜索树的初始状态，即dfs的起点
    return 0;
}



// 4. 优化一维数组
// 将二维数组 dp 优化为一维数组，通过逆序遍历背包容量，实现了滚动数组的效果
#include <iostream>
#include <algorithm>
#include <vector>
#define MAXN 1010
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> v(n + 1, 0);
    vector<int> w(n + 1, 0);
    vector<int> dp(MAXN, 0); // 优化为一维数组

    // 输入每个物品的体积和价值
    for (int i = 1; i <= n; i++)
        cin >> v[i] >> w[i];

    // 动态规划过程
    for (int i = 1; i <= n; i++)
    {
        for (int j = m; j >= v[i]; j--)
        {
            dp[j] = max(dp[j], dp[j - v[i]] + w[i]);
        }
    }

    cout << dp[m] << endl; // 输出结果
    return 0;
}