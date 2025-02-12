#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int dp[10010] = {0};

    int dfs(vector<int> &nums, int x)
    {
        // 要写在记忆化之前 否则越界
        if (x < 0)
            return 0;

        if (dp[x])
            return dp[x];

        int res = -1e9;
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