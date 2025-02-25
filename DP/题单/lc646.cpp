// 1. 差点过了
// 原代码中对于能否将当前数对添加到链中的判断条件是 next > prev，即当前数对的第一个元素大于前一个数对的第二个元素。但是，这种判断逻辑没有考虑到最优子结构的问题。在动态规划求解最长链时，应该遍历之前的所有数对，检查是否能将当前数对添加到以某个之前的数对结尾的链中，从而得到更长的链。原代码只是简单地与前一个数对比较，可能会错过一些更优的链组合。

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // 必须使用静态成员变量 否则报错
    static bool cmp(const vector<int> &a, const vector<int> &b)
    {
        if (a[0] != b[0])
            return a[0] < b[0];
        return a[1] < b[1];
    }
    int findLongestChain(vector<vector<int>> &pairs)
    {
        sort(pairs.begin(), pairs.end(), cmp);
        int n = pairs.size();
        vector<int> dp(n + 1); // 前i行数组组成的最长对

        dp[0] = 1;
        int prev = pairs[0][1];
        int next;
        for (int i = 1; i < n; i++)
        {
            next = pairs[i][0];
            // 每每处理最后一个数对时 有两种情况
            // 1. 可以直接接上去
            // 2. 无法接上去。但由于数组是排序的，既然i-1能接上i-2，那i也能接上i-2.所以要选择是否替换
            if (next > prev)
            {
                dp[i] = dp[i - 1] + 1;
                prev = pairs[i][1];
            }
            else
            {
                dp[i] = dp[i - 1];
                prev = min(pairs[i - 1][1], pairs[i][1]); // 选一个较小的作为前驱，即选择替换与否
            }
        }
        return dp[n - 1];
    }
};



// 2. 修改版本
// 起始这种模型很常见，二层for，第二层遍历i之前的元素
class Solution
{
public:
    // 必须使用静态成员变量 否则报错
    static bool cmp(const vector<int> &a, const vector<int> &b)
    {
        if (a[0] != b[0])
            return a[0] < b[0];
        return a[1] < b[1];
    }
    int findLongestChain(vector<vector<int>> &pairs)
    {
        sort(pairs.begin(), pairs.end(), cmp);
        int n = pairs.size();
        vector<int> dp(n, 1); // 前i行数组组成的最长对

        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (pairs[i][0] > pairs[j][1])
                    dp[i] = max(dp[i], dp[j] + 1);
            }
        }

        int ans = 0;
        for (int i = 0; i < n; i++)
            ans = max(ans, dp[i]);
        return ans;
    }
};