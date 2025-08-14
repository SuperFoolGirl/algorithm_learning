// 感觉越来越往数学推理的方向靠拢了
// 而且我的方法也有问题 还是没有贯彻五步法

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int numDecodings(string s)
    {
        int n = s.size();
        vector<int> f(n + 1);
        f[0] = 1;
        for (int i = 1; i <= n; ++i)
        {
            if (s[i - 1] != '0')
                f[i] += f[i - 1];
            if (i > 1 && s[i - 2] != '0' && ((s[i - 2] - '0') * 10 + (s[i - 1] - '0') <= 26))
                f[i] += f[i - 2];
        }
        return f[n];
    }
};