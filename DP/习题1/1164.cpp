/*
讲一下相加逻辑和取最值逻辑的区别：
1. 取最大值的逻辑通常用于求解最优解问题，比如求最大价值、最长路径、最大收益等。在这类问题中，我们需要在多个可选的决策中选择能使目标值达到最大的那个决策。每一个状态的最优解取决于它之前状态的最优解，并且在不同的转移路径中，我们只关注能带来最大结果的那条路径。
2. 相加的逻辑一般用于求解方案数问题，也就是计算满足特定条件的所有可能方案的总数。在这种情况下，每一种可能的决策都会产生一种新的方案，我们需要把所有可能决策产生的方案数累加起来，得到当前状态的总方案数。
3. 其他逻辑还有取最小值、相乘等，遇到再细说
*/

#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> dp(110, vector<int>(10000, 0)); // dp[i][j] = 选到第i个菜品后，还剩j元的方案数(i-n)
int n, m;
vector<int> menu(110, 0);

int dfs(int x, int money)
{
    if (dp[x][money])
        return dp[x][money];

    // 这里一开始想得太简单了啊！出口要处理基准情形啊，这是递归的基本结构
    if (x > n)
    {
        if (money == m)
            return 1; // 选到最后一个菜品，且正好花完了m元，方案自然只能是1，都写满了。这一点要好好理解
        return 0;
    }

    // 干掉sum 直接记忆化
    if (money + menu[x] <= m) // 可以选 也可以不选。但这里的逻辑是相加，不是取最大值。即当前状态为选或不选的方案数之和
        dp[x][money] = dfs(x + 1, money) + dfs(x + 1, money + menu[x]);
    else // 不能选
        dp[x][money] = dfs(x + 1, money);

    return dp[x][money];
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> menu[i];
    cout << dfs(1, 0);
    return 0;
}
