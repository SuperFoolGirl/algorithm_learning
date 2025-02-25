#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int countGoodStrings(int low, int high, int zero, int one)
    {
        long long mod = 1e9 + 7;
        vector<long long> dp(high + 1);

        // 这个初始化结合下面的for循环 好好体会一下
        dp[0] = 1;

        for (int i = 1; i <= high; i++)
        {
            // 两个if改成取等了。取等后，会发现之前写的基准条件dp[one]和dp[zero]其实就变成dp[0]了
            // 注意这里取模的处理。不能等到最后再取模，那样已经越界了；同时，从数学角度可以证明，每一次相加都进行取模，与最后一起取模，结果相同
            if (i >= zero)
                dp[i] = (dp[i] + dp[i - zero]) % mod;
            if (i >= one)
                dp[i] = (dp[i] + dp[i - one]) % mod;
        }

        long long ans = 0;
        for (int i = low; i <= high; i++)
            ans = (ans + dp[i]) % mod;
        return ans % mod;
    }
};