#include <bits/stdc++.h>
using namespace std;

// 差点想出来
class Solution
{
public:
    int numSquares(int n)
    {
        vector<int> f(n + 1);
        for (int i = 1; i <= n; i++)
        {
            int minn = INT_MAX;
            for (int j = 1; j * j <= i; j++) // 这个范围牛皮
            {
                minn = min(minn, f[i - j * j]);
            }
            f[i] = minn + 1; // 遍历所有的才出结果。不要以为dp万能。
        }
        return f[n];
    }
};