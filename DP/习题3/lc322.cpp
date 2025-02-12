// 1. 完全背包模板
// 第一眼没看出来是完全背包 太他妈菜了
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        int n = coins.size();
        vector<vector<int>> dp(n + 1, vector<int>(amount + 1, 1e9)); // 初始化无穷大是为了后面的min

        // 初始化：使用前 0 种硬币凑出金额 0 需要 0 个硬币
        // 众所周知 每次写dp的基准情况都很折磨
        // 那我们不妨换个思路：根据ij的起始情况来写
        // 比如这个题ij都是从0开始的
        dp[0][0] = 0;

        // 这里讲一下为什么又出现了状态转移方程的反转
        // 力扣给的数组是从0开始存的，不符合之前从1开始的习惯
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j <= amount; j++)
            {
                if (j >= coins[i])
                    dp[i + 1][j] = min(dp[i][j], dp[i + 1][j - coins[i]] + 1); // 后面的情况由前面转移而来
                else
                    dp[i + 1][j] = dp[i][j];
            }
        }

        if (dp[n][amount] == 1e9)
            return -1;
        else
            return dp[n][amount];
    }
};



// 2. 套用五步法
// 这个题很震撼 可以清晰地对比背包模板和五步法写出来的差异
// 通过这个写法，可以看出来五步法的泛用性更广，写起来更自由舒服。但思维量要大一些

/*
1. 重述问题
    用最少的硬币数凑成amount(可以无限选 完全背包模型)
2. 最后一步
    选择了某个硬币，使金额凑到了amount
3. 去掉最后一步，问题变成了
    用最少的硬币数凑成amount-coins[i]
4. 和并整理问题
    f(amount) = min(f(amount-coins[i])) + 1
5. 边界问题
*/

class Solution
{
public:
    int dp[10010] = {0};

    int dfs(vector<int> &coins, int amount) // amount表示剩余的钱
    {
        // 预处理
        int n = coins.size();
        if (dp[amount])
            return dp[amount];

        // 特判兼出口
        if (amount == 0)
            return 0;

        // 最后一步：选择了某个硬币，使金额凑成
        int res = 1e9;
        for (int i = 0; i < n; i++)                                // 遍历最后的硬币
            if (amount >= coins[i])                                // 有了这句 其实就不会出现amount小于0的情况
                res = min(res, dfs(coins, amount - coins[i]) + 1); // 这里不能直接return了 我们要不断更新最好的情况

        dp[amount] = res;
        return dp[amount];
    }

    int coinChange(vector<int> &coins, int amount)
    {
        int ans = dfs(coins, amount);
        return ans == 1e9 ? -1 : ans;
    }
};

/*
说一下res的问题
直接用dp[amount]来代替res进行压行，会导致一些操作无法实现
比如本题中res要先赋值为无穷大 如果直接用dp[amount]的话 还得额外给一个赋值函数
但dp数组太大了 这样做会很占用空间
所以不要无脑用dp数组来代替res
*/



// 3. 五步法改dp
// 别硬想模板 稍微想一下递归搜索树就能写出来
// 当然也可以简单总结一下：外层for循环遍历的是dp的下标，内层遍历的是“最后一步”或“最后一步带来的衍生问题”
// 毕竟递推的进行依赖的是dp下标从小到大
// 外层遍历dp下标一般从1开始；0是基准情况
class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        vector<int> dp(10010, 1e9);
        int n = coins.size();

        // 基准情形
        dp[0] = 0;
        for (int i = 1; i <= amount; i++) // 遍历dp以递推
        {
            for (int j = 0; j < n; j++) // 遍历结尾
            {
                if (coins[j] <= i)
                    dp[i] = min(dp[i], dp[i - coins[j]] + 1);
            }
        }
        return dp[amount] == 1e9 ? -1 : dp[amount];
    }
};

/*
说几个细节
1. 相比完全背包写法 dp数组降了一维
2. 前面讲过for循环顺序：外层顺序遍历dp下标且从1开始
3. 由于dp数组降维和两个for循环，基准情况只能是dp[0], 根据题意赋值即可
4. 在五步法下，dfs和顺序递推的dp数组、状态转移方程完全相同(感觉这才是真正意义上的动态规划)
*/