// 耻辱 不会做
/*
每个房子可以被粉刷成三种颜色中的一种，需要计算在满足相邻房子的颜色不同的情况下粉刷所有房子的最小花费成本。由于当已知粉刷前 i 个房子的最小花费成本时，根据粉刷第 i+1 号房子的花费成本可以计算粉刷前 i+1 个房子的最小花费成本，因此可以使用动态规划计算最小花费成本。
dp[i][0]=min(dp[i−1][1],dp[i−1][2])+costs[i][0]
dp[i][1]=min(dp[i−1][0],dp[i−1][2])+costs[i][1]
dp[i][2]=min(dp[i−1][0],dp[i−1][1])+costs[i][2]
合并得：
dp[i][j]=min(dp[i−1][(j+1)%3],dp[i−1][(j+2)%3])+costs[i][j]
这种题我根本就没想到用模来表示
*/
// 由状态转移方程可知 可以进行滚动数组优化
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
    int minCost(vector<vector<int>> &costs)
    {
        vector<int> dp(3);
        int n = costs.size();

        for (int i = 0; i < 3; i++)
            dp[i] = costs[0][i];

        vector<int> tmp(3);
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < 3; j++)
                tmp[j] = min(dp[(j + 1) % 3], dp[(j + 2) % 3]) + costs[i][j];
            dp = tmp;
        }
        return *min_element(dp.begin(), dp.end()); // algorithm库中的函数
    }
};