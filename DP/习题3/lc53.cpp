#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int dp[10010] = {0};

    int dfs(vector<int> &nums, int x)
    {
        // 要写在记忆化之前 否则越界
        if (x < 0) // x是nums的下标
            return 0;

        if (dp[x])
            return dp[x];

        int res = -1e9;
        // 只选择第 x 个元素，即 nums[x]。也就是以nums[x]结尾的连续子数组的最大和就是 nums[x]。
        // 选择第 x 个元素，并将其加入到以第 x - 1 个元素结尾的连续子数组中，即 dfs(nums, x - 1) + nums[x]。 这就实现了拆解子问题
        // 不妨深入这个子问题画递归搜索树：不断选择x-1，直到x<0，这样就实现了下标从0到x全选了
        // 因此递归搜索树的模样就是以nums[x]为起点，不断向下扩大的这样一个过程。

        // 注意区分与最长递增子序列的区别，它是不连续的，而最大区间和是连续的
        // 所以本题用不上for循环，而且参数二是x-1，直接去找x的上一位
        res = max(nums[x], dfs(nums, x - 1) + nums[x]);
        dp[x] = res;
        return dp[x];
    }

    int maxSubArray(vector<int> &nums)
    {
        int ans = -1e9;
        int n = nums.size();
        for (int i = 0; i < n; i++) // 遍历结尾
            ans = max(ans, dfs(nums, i));
        return ans;
    }
};

/*
讲一下最长递增子序列和最大区间和的区别：
1. 最长递增子序列，dfs内使用for循环
在计算以第 i 个元素结尾的最长递增子序列长度时，需要考虑它能接在前面哪些元素结尾的递增子序列后面。因此需要遍历 i 前面的所有元素 j，判断是否满足递增条件，如果满足则更新 dp[i]。所以需要在 DFS 内部使用 for 循环来遍历前面的元素。
2. 最大区间和，dfs内不使用for循环
在计算以第 i 个元素结尾的连续子数组的最大和时，只需要考虑它是否要和以第 i - 1 个元素结尾的连续子数组合并。因为是连续子数组，不需要考虑前面其他位置的元素，所以不需要使用 for 循环来遍历前面的元素，只需要直接根据 dp[i - 1] 来更新 dp[i] 即可。
*/