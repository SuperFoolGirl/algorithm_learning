// 最后一步：找到第k个数x凑成n 使得乘积最大化
// 去掉最后一步：找到第k-1个数凑成n-x，使得乘积最大化
// 做法：遍历第k个数x，找到最大的dp[n-x]*x
// 子结构最优：如果每一步都是乘积最大，那最终也是乘积最大


// 1. 搜索dfs
// 不写写这个我都忘了当初学的搜索dfs咋写了hh
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int ans = 0;

    void dfs(int n, int x, int mul, int start)
    {
        if (x == n)
        {
            ans = max(ans, mul);
            return;
        }

        for (int i = start; i < n; i++)
            if (x + i <= n)
                dfs(n, x + i, mul * i, i);
    }

    int integerBreak(int n)
    {
        dfs(n, 0, 1, 1);
        return ans;
    }
};


// 2. 动态规划dfs
// 我发现很多时候自己不够大胆
// 强调下本题中dp数组的含义：dp[i]表示拆分数字i后可以得到的最大乘积
class Solution
{
public:
    int dp[60] = {0};
    int dfs(int x)
    {
        // 出口一般都是考虑0 可以代入试一下
        // 解释一下：拆到剩下0，说明恰好拆完，返回一个1，乘积不变
        if (x == 0)
            return 1;

        if (dp[x])
            return dp[x];

        int res = 0;
        // 遍历最后一个数，也就是遍历拆分方式
        // 还是回到拆分子问题那个环节
        // 最后一步是遍历第k个数x，找到最大的dp[n-x]*x
        // 但要完成这一步，又需要找第k-1个数...
        // k,k-1,k-2依次作为要遍历的最后一个数
        // 因此 看似我们通过五步法写出了 写出最后一步 和 去掉最后一步
        // 但进入“去掉最后一步”后，这个环节里面的最后一步又变成了“最后一步”
        // 串联起来后，整个过程就变成了“遍历拆分方式”

        // 仔细想一下 这是一种很正宗、原汁原味的思考方式 只是一直被我有所忽略
        // 此前一直无脑跟着五步法来写 但并没过多思考
        // 实际上 根据五步法写出后，稍微模拟一下递归路径 会发现 的确是合理的

        for (int i = 1; i < x; i++)
            // 这里要比较三个数 参数2为只拆成两个数的情况
            // 如果去掉参数二 会导致只拆成两个数的情况被忽略 这是数学问题
            res = max(res, max(i * (x - i), dfs(x - i) * i)); 
        dp[x] = res;
        return res;
    }

    int integerBreak(int n)
    {
        return dfs(n);
    }
};




// 3. dp
// 注意递归本身占用一个for循环 借此推测dp中for循环的层数
// 注意本题的思考过程
// 对于较难的题目 dp也不能无脑改写
class Solution
{
public:
    int integerBreak(int n)
    {
        vector<int> dp(n + 1, 0); // dp[n]代表n被拆分后的最大乘积
        // 首先可以判断 在逻辑上 应该写成两层for循环
        // 递归本身算一个循环体 再加上递归内部的for循环
        // 回忆下递归的逻辑：对于拆出来的x-i，再进行新一轮的从1开始的拆分
        // 因此 外层循环遍历dp下标 也就是每个数被拆分后的最大乘积，然后逐渐递推到dp[n]
        // 内层循环遍历拆分方法
        // 这样是符合逻辑的

        // 题目数据n最小是2，因此直接处理dp[1]
        dp[1] = 0;
        // 遍历要拆的数
        for (int i = 2; i <= n; i++)
            // 遍历拆法
            for (int j = 1; j < i; j++) // 不能取等是因为至少拆成两个数
                dp[i] = max(dp[i], max(j * (i - j), dp[i - j] * j));

        return dp[n];
    }
};
