// 完全背包问题

// 1. dfs
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define maxn 1010

int N, V;
vector<int> v(maxn, 0);
vector<int> w(maxn, 0);
vector<vector<int>> dp(maxn, vector<int>(maxn, 0)); // 选到第i个物品，背包容量为j后的最大价值

int dfs(int x, int V)
{
    if (x > N)
        return 0;
    if (dp[x][V])
        return dp[x][V];

    if (V >= v[x])
        return dp[x][V] = max(dfs(x + 1, V), dfs(x, V - v[x]) + w[x]); // 注意变动点：选了之后还能再选
    return dp[x][V] = dfs(x + 1, V);
}

int main()
{
    cin >> N >> V;
    for (int i = 1; i <= N; i++)
        cin >> v[i] >> w[i];
    cout << dfs(1, V);
    return 0;
}



// 2. 顺序递推
// 无法改成滚动数组 因为dp[i-1]被打破了
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define maxn 1010

int N, V;
vector<int> v(maxn, 0);
vector<int> w(maxn, 0);
vector<vector<int>> dp(maxn, vector<int>(maxn, 0)); // 选到第i个物品，背包容量为j时的最大价值

int main()
{
    cin >> N >> V;
    for (int i = 1; i <= N; i++)
        cin >> v[i] >> w[i];

    // 隐含dp[0][j] = 0
    for (int i = 1; i <= N; i++)
    {
        for (int j = 0; j <= V; j++)
        {
            if (j >= v[i])
                dp[i][j] = max(dp[i - 1][j], dp[i][j - v[i]] + w[i]); // 本次状态依赖两点：上个状态a没选a而跳到这里b；本次状态b选了b
            else
                dp[i][j] = dp[i - 1][j];
        }
    }
    cout << dp[N][V];
    return 0;
}



// 01背包倒序的目的就是 保证每个物品只选一次
// 01背包如果正序枚举体积，就会让物品拿多次
// 但这恰好符合完全背包的要求，所以完全背包的正序枚举体积

// 3. 顺序递推优化一维数组
/*
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define maxn 1010

int N, V;
vector<int> v(maxn, 0);
vector<int> w(maxn, 0);
vector<int> dp(maxn, 0);

int main()
{
    cin >> N >> V;
    for (int i = 1; i <= N; i++)
        cin >> v[i] >> w[i];

    // 隐含dp[0][j] = 0
    for (int i = 1; i <= N; i++)
        for (int j = v[i]; j <= V; j++) // 从v[i]开始正序枚举
            dp[j] = max(dp[j], dp[j - v[i]] + w[i]);

    cout << dp[V];
    return 0;
}
*/