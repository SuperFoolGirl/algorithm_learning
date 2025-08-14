// 01背包求体积恰好为M的方案数

// 1. dfs TLE了
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define maxn 110

int n, m;
vector<int> nums(maxn, 0);
vector<vector<int>> dp(maxn, vector<int>(10010, 0)); // 选到第i个数，还剩j需要选，在此之后的最大方案数

int dfs(int x, int rest)
{
    if (dp[x][rest])
        return dp[x][rest];
    if (x > n)
    {
        if (rest == 0)
            return 1;
        return 0;
    }

    // 这个题求方案总数 不是最好情况 因此用的是加法逻辑
    if (rest >= nums[x])
        return dp[x][rest] = dfs(x + 1, rest) + dfs(x + 1, rest - nums[x]);
    return dp[x][rest] = dfs(x + 1, rest);
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> nums[i];
    cout << dfs(1, m);
    return 0;
}



// 2. 顺序递推
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define maxn 110

int n, m;
vector<int> nums(maxn, 0);
vector<vector<int>> dp(maxn, vector<int>(10010, 0)); // 选到第i个数，还剩j需要选，此时的最大方案数

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> nums[i];

    // 隐含的base case：dp[0][j] = 0
    // 其他base case：dp[i][0] = 1
    // 正确认识dfs的出口与递推的基准情形的关系：二者是一致的
    // 既然本题型是在dfs出口处进行改动，那递推也应该在基准情形的设置处进行改动
    for (int i = 1; i <= n; i++)
        dp[i][0] = 1;

    // 注意这个特殊情况
    // 有点抽象 但在写递推的时候，不得不品鉴
    // 只能说多做题培养题感吧
    dp[0][0] = 1;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            if (j >= nums[i])
                dp[i][j] = dp[i - 1][j] + dp[i - 1][j - nums[i]];
            else
                dp[i][j] = dp[i - 1][j];
        }
    }
    cout << dp[n][m];
    return 0;
}



// 3. 优化空间
/*
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define maxn 110

int n, m;
vector<int> nums(maxn, 0);
vector<int> dp(10010, 0);

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> nums[i];

    // 想想我们优化前基准情况是怎么写的：dp[i][0] = 0
    dp[0] = 1;

    for (int i = 1; i <= n; i++)
        for (int j = m; j >= nums[i]; j--)
            dp[j] = dp[j] + dp[j - nums[i]];
    cout << dp[m];
    return 0;
}
*/