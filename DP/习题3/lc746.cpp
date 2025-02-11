#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
下面是我的写法，不如标准答案简洁
缺乏经验，对dp数组的定义太老套，不够灵活变通
如果将dp定义改为“到达本层所需要的钱”，也就是不包括往外跳的那一步，就简洁很多了。下面会给出。
*/
class Solution
{
public:
    int minCostClimbingStairs(vector<int> &cost)
    {
        int target = cost.size();
        cost.resize(target + 2); // 防止越界，扩容部分初始化为0。恰好使得最顶层cost[target] = 0
        vector<int> dp(1010, 0); // 处于当前层数共花费的钱数，包括往外跳的那一步
        int ans = 0x7fffffff;

        // 1. 从0开始
        // 基准情形
        dp[0] = cost[0];
        dp[1] = cost[0] + cost[1];
        for (int i = 2; i <= target; i++) // dp[target]恰好是顶部 数组的下一位
            dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];
        ans = min(ans, dp[target]);

        // 2. 从1开始
        dp.clear();
        dp[1] = cost[1];
        dp[2] = cost[1] + cost[2];
        for (int i = 3; i <= target; i++)
            dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];
        ans = min(ans, dp[target]);

        return ans;
    }
};




// 法二
class Solution
{
public:
    int minCostClimbingStairs(vector<int> &cost)
    {
        int n = cost.size();
        int dp[1010];
        dp[0] = dp[1] = 0; // 这两个是起始点，一分钱不花就可以到达。这里是真的巧妙，还避免了我上面的跑两次

        for (int i = 2; i <= n; i++)
            dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);

        return dp[n];
    }
};

/*
用四步法来解释思路
1. 重述问题：
    从第0/1层开始爬，每层花费cost[i]，一直爬到n层，求最小花费
2. 找到最后一步
    爬一层到顶 / 爬两层到顶
3. 去掉最后一步，问题变成了什么？
    爬到n-1层的最小花费 / 爬到n-2层的最小花费
4. 合并整理问题
    原问题为爬到n层的最小花费，等于爬到n-1层的最小花费 + cost[n-1] / 爬到n-2层的最小花费 + cost[n-2]
5. 考虑边界
    dp[0] = dp[1] = 0，因为这两个是起始点，一分钱不花就可以到达
    就是平时要找的那些基准情形
*/