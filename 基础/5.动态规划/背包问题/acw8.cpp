// 二维费用的背包问题

// 记忆化搜索+dfs的递推写法，dfs函数参数个数与dp数组的维度相同
// 因此递归才能改写成递推

// 三维dp数组一般都会MLE，因此需要优化

// 1. dfs 由于dfs的递归树是三维的，无法优化
#include <iostream>
#include <vector>
#include <algorithm>
#define maxn 1010
using namespace std;

int N, V, M;
vector<int> v(maxn, 0); // vector必须初始化才能当数组用，否则只能push_back
vector<int> m(maxn, 0);
vector<int> w(maxn, 0);
// 别乱初始化大小 看准数据范围
vector<vector<vector<int>>> dp(maxn, vector<vector<int>>(110, vector<int>(110, 0))); // dp[i][j][k]表示i个物品，容量为j，重量为k后的最大价值

int dfs(int x, int V, int M)
{
    if (dp[x][V][M])
        return dp[x][V][M];
    if (x > N)
        return 0;

    if (V >= v[x] && M >= m[x])
        return dp[x][V][M] = max(dfs(x + 1, V, M), dfs(x + 1, V - v[x], M - m[x]) + w[x]);
    return dp[x][V][M] = dfs(x + 1, V, M);
}

int main()
{
    cin >> N >> V >> M;
    for (int i = 1; i <= N; i++)
        cin >> v[i] >> m[i] >> w[i];
    cout << dfs(1, V, M);
    return 0;
}



// 2. 未优化顺序递推
#include <iostream>
#include <vector>
#include <algorithm>
#define maxn 1010
using namespace std;

int N, V, M;
vector<int> v(maxn, 0); // vector必须初始化才能当数组用，否则只能push_back
vector<int> m(maxn, 0);
vector<int> w(maxn, 0);
vector<vector<vector<int>>> dp(maxn, vector<vector<int>>(110, vector<int>(110, 0))); // dp[i][j][k]表示前i个物品，容量为j，重量为k的最大价值

int main()
{
    cin >> N >> V >> M;
    for (int i = 1; i <= N; i++)
        cin >> v[i] >> m[i] >> w[i];

    // 隐含的初始化：dp[0][j][k] = 0
    for (int i = 1; i <= N; i++)
        for (int j = 0; j <= V; j++)
            for (int k = 0; k <= M; k++)
            {
                if (j >= v[i] && k >= m[i])
                    dp[i][j][k] = max(dp[i - 1][j][k], dp[i - 1][j - v[i]][k - m[i]] + w[i]);
                else
                    dp[i][j][k] = dp[i - 1][j][k];
            }
    cout << dp[N][V][M]; // 表示考虑所有 N 个物品，容量为 V，重量为 M 时的最大价值。但注意，这三个指标不一定都填满，只是表示都考虑到的意思，即物品的最大范围是N，背包的最大范围是V和M
    return 0;
}



// 3. 优化顺序递推
// 滚动数组只能优化一个维度，三维变两维
// 优化的那个维度是最外层维度。回顾一下滚动数组原理，我们之所以能优化是因为dp[i-1]是共同出现的
/*
    for (int i = 1; i <= N; i++)
        // 这两个循环都要倒序。dp[i][j][k]依赖于dp[i-1][j][k]和dp[i-1][j-v[i]][k-m[i]]
        for (int j = V; j >= 0; j--)
            for (int k = M; k >= 0; k--)
            {
                if (j >= v[i] && k >= m[i])
                    dp[j][k] = max(dp[j][k], dp[j - v[i]][k - m[i]] + w[i]);
            }
    cout << dp[V][M]; // dp[N][V][M] -> dp[V][M]
*/
// 不过 还能再简化一下
/*
    for (int i = 1; i <= N; i++)
        for (int j = V; j >= v[i]; j--)
            for (int k = M; k >= m[i]; k--)
                dp[j][k] = max(dp[j][k], dp[j - v[i]][k - m[i]] + w[i]);

    直接将遍历范围限制在能够装下第 i 个物品的容量和重量范围内，避免了大量不必要的判断。只有当容量和重量足够时才会更新状态，减少了不必要的计算，提高了代码的效率
    原本有一句dp[i][j][k] = dp[i-1][j][k]，但是这句话是多余的，因为dp[j][k]的值在之前的循环中已经被更新过了，j即已经隐式地完成了该操作。所以这句话可以省略
    对于j,k不满足条件的情况，直接不会进入max更新。然后最外层i往前推进，其实就隐式地完成了dp[i][j][k] = dp[i-1][j][k]的操作
*/