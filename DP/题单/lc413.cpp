#include <iostream>
#include <vector>
using namespace std;

// 1. 题解
class Solution
{
public:
    int numberOfArithmeticSlices(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 1)
        {
            return 0;
        }

        int d = nums[0] - nums[1], t = 0;
        int ans = 0;
        // 因为等差数列的长度至少为 3，所以可以从 i=2 开始枚举
        for (int i = 2; i < n; ++i)
        {
            if (nums[i - 1] - nums[i] == d)
            {
                ++t;
            }
            else
            {
                // 如果当前元素和前一个元素的差值不等于 d，说明等差数列中断了，更新 d 为当前元素和前一个元素的差值，并将 t 重置为 0
                d = nums[i - 1] - nums[i];
                t = 0;
            }
            ans += t; // 很巧妙
            // 举个例子 如果前面1234构成了123 234 1234 3个串
            // 下一个是5的话 就有1234 2345 12345这3个在原来基础上增加一位+456 得到3+1=4个串
        }
        return ans;
    }
};



// 2. dp 思路相同 写法不一样
class Solution
{
public:
    int numberOfArithmeticSlices(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 1)
            return 0;
        vector<int> dp(n);
        int d = nums[1] - nums[0];
        int ans = 0;
        for (int i = 2; i < n; i++)
        {
            if (nums[i] - nums[i - 1] == d)
                dp[i] = dp[i - 1] + 1;
            else
                d = nums[i] - nums[i - 1];
            ans += dp[i];
        }
        return ans;
    }
};