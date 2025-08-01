// 下标i表示队列里还有几个待排的数，j表示栈里有j个数
// 一时间真没想到怎么设变量

// 1. 递归写法
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 20
using namespace std;

int n;
vector<vector<int>> dp(MAXN, vector<int>(MAXN, 0)); // dp[i][j]表示队列里还有i个数，栈里有j个数的情况下的方案数

int dfs(int x, int y)
{
    if (dp[x][y])
        return dp[x][y];

    // 边界条件
    if (x == 0 && y == 0)
        return 1; // 这个状态下只有一种情况

    // 对于每个状态，转移到下个状态有两种选择：从外部队列取一个压栈，或者自己出栈
    // 但要搞清楚出栈的实质
    // 两种选择的方案数相加即为当前状态的方案数
    int sum = 0;
    if (x > 0)
        sum += dfs(x - 1, y + 1); // 从外部队列取一个压栈
    if (y > 0)
        sum += dfs(x, y - 1); // 自己出栈

    return dp[x][y] = sum; // 压行
}

int main()
{
    cin >> n;
    cout << dfs(n, 0); // 初始状态是队列里有n个数，栈里有0个数。队列指的是外部序列
    return 0;
}



// 2. 逆序递推写法
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 20
using namespace std;

int n;
vector<vector<int>> dp(MAXN, vector<int>(MAXN, 0)); // dp[i][j]表示队列里还有i个数，栈里有j个数的情况下的方案数

int main()
{
    cin >> n;
    dp[0][0] = 1; // 这个情况是已经完成的状态，栈和队列里都没东西了
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            // 逆序考虑
            if (i > 0) // 如果队列里面有，说明可以压栈。当前状态可由dp[i-1][j+1]push得到，也就是压栈后的状态
                dp[i][j] += dp[i - 1][j + 1]; // 队列-1，栈+1
            if (j > 0) // 如果栈里面有，说明可以弹出。当前状态可由dp[i][j-1]pop得到，也就是弹出后的状态
                dp[i][j] += dp[i][j - 1]; // 队列不变，栈-1
        }
    }
    cout << dp[n][0];
    return 0;
}


// 3. 顺序递推
// 第一次遇到：dp数组含义相同
// 这个题其实也能感受出来，数组含义不太容易能想到互补的点
// 状态转移公式那里确实不好理解，甚至有点因果律和推理的味道
// dp数组不变，i和j只是确定是否有压栈和弹出资格
// 这两个操作决定了一个状态的两个组成部分。同时因为顺序逆序不同，所以状态转移方程也不同
// 举个例子。如果i>0，有压栈资格。设当前状态为a，压栈后的状态为b。逆序递推时，a是由b得到的。顺序递推时，b是由a得到的
// 上一句话说得非常好。可以很好地理解状态转移方程的两个写法了
// 说实话还是dfs最容易理解。。
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 20
using namespace std;

int n;
vector<vector<int>> dp(MAXN, vector<int>(MAXN, 0)); // dp[i][j]表示队列里还有i个数，栈里有j个数的情况下的方案数

int main()
{
    cin >> n;

    // 这里是强行给了个基准情况。其实不合理。这题要写的话，还是应该用逆序
    dp[n][0] = 1;

    for (int i = n; i >= 1; i--)
    {
        for (int j = 0; j <= n; j++)
        {
            // 注意这里的顺序 顺序不同是状态转移方程不同的体现
            // 说实话 思维量确实偏大
            // 这里遍历到某个状态时，是用于恢复上一个状态的

            if (i > 0) // 如果队列不空，那可以执行压栈。压栈前的状态可由当前得到
                dp[i - 1][j + 1] += dp[i][j];
            if (j > 0) // 如果栈不空，那可以执行出栈。出栈前的状态可由当前得到
                dp[i][j - 1] += dp[i][j];
        }
    }
    cout << dp[n][0]; // 出口居然和入口相同 可想而知这个顺序递推多么扭曲
    return 0;
}