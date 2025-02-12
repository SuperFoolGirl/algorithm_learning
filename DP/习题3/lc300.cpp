/*
首先弄清楚子序列和子数组的区别

1. 重述问题
    在一个长度为n的数组中，找到一个最长的递增子序列，返回其长度
2. 找到最后一步
    选择了某个数x作为最长递增子序列的结尾
3. 去掉最后一步 拆解子问题
    问题变成了在x之前的数中找到一个最长的递增子序列(序列有很多，找最长的)
4. 和并整理问题
    问题变成了在x之前的数中找到一个最长的递增子序列，然后加上1
5. 边界问题
    无边界。数组长度就是边界。
*/

// 这个题我果然没写出来
// 因为我还在套用之前的思路
// for循环在dp的使用 我接触的不多
// for循环在dp中的理念：子结构最优
// 如果子问题都是最优解，那么整体问题也是最优解

// 根据以往的经验，我想用dfs一次性跑出来
// 但是结果说明，每一个点做起点，都有可能是最长的递增子序列
// 这一点就需要for循环，让每个点作为起点，跑dfs



// 1. dfs 无记忆化搜索
// 这段代码完全按照五步在写，尤其是通过“2.最后一步”为本题的搜索写法奠基
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int dfs(vector<int> &nums, int x)
    {
        int res = 1; // 初始化结果为 1，因为每个元素自身都可以构成一个长度为 1 的递增子序列。
        for (int i = 0; i < x; i++)
            if (nums[i] < nums[x]) // 注意这个比较基准：nums[x]，来源于遍历的结尾
                res = max(res, dfs(nums, i) + 1); // 取最值的思想我掌握得还不好
        return res;
    }

    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        int ans = -1;
        // 回忆下最后一步：选择某个数作为最长递增子序列的结尾
        // 因此每个数都有可能是结尾
        for (int i = 0; i < n; i++) // 遍历结尾
            ans = max(ans, dfs(nums, i));
        return ans;
    }
};



// 2. 记忆化搜索
// 不觉得res很眼熟吗 就是sum啊！
class Solution
{
public:
    int dp[2510] = {0}; // dp[x] 表示以 nums[x] 结尾的最长递增子序列的长度
    int dfs(vector<int> &nums, int x)
    {
        if (dp[x])
            return dp[x];

        dp[x] = 1;
        for (int i = 0; i < x; i++) // 遍历开头 在给定区间内找最长序列
            if (nums[i] < nums[x])
                dp[x] = max(dp[x], dfs(nums, i) + 1);
        return dp[x];
    }

    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        int ans = -1;
        for (int i = 0; i < n; i++) // 遍历结尾
            ans = max(ans, dfs(nums, i));
        return ans;
    }
};




// 3. dp
class Solution
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        vector<int> dp(2510, 0);
        int n = nums.size();

        for (int i = 0; i < n; i++) // 遍历结尾，即遍历dp
        {
            dp[i] = 1; // 仔细观察，不会覆盖之前的dp值
            for (int j = 0; j < i; j++) // 遍历开头，以确定区间
                if (nums[j] < nums[i])
                    dp[i] = max(dp[i], dp[j] + 1);
        }

        // 现在dp储存了每个结尾的最长递增子序列，只需要找最大值即可
        int ans = 0;
        for (int i = 0; i < n; i++)
            ans = max(ans, dp[i]);

        return ans;
    }
};