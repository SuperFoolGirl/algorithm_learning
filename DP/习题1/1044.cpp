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
    dp[0][0] = 1;
    // dfs起点是(n, 0)，终点是(0, 0)。逆序递推相反
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            // 逆序考虑
            if (i > 0) // 如果队列里面有，说明可以压栈。当前状态可由dp[i-1][j+1]push得到
                dp[i][j] += dp[i - 1][j + 1]; // 队列-1，栈+1
            if (j > 0) // 如果栈里面有，说明可以弹出。当前状态可由dp[i][j-1]pop得到
                dp[i][j] += dp[i][j - 1]; // 队列不变，栈-1
        }
    }
    cout << dp[n][0];
    return 0;
}


// 3. 顺序递推
// 第一次遇到：dp数组含义相同
// 这个题其实也能感受出来，数组含义不太容易能想到互补的点
// 状态转移公式那里确实不好理解
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

    // 当 i = n 且 j = 0 时，意味着队列里有完整的 n 个数，分别是 1, 2, ..., n，而栈是空的。这是整个操作过程的起始状态，此时还没有进行任何入栈或者出栈操作。对于这个特定的起始状态，它是唯一确定的一种情况，不存在多种可能的状态组合，所以方案数为 1。
    dp[n][0] = 1;

    // dfs起点是(n, 0)，终点是(0, 0)。顺序递推相同
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
    cout << dp[n][0];
    return 0;
}