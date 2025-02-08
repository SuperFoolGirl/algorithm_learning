// 1. dfs
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define maxn 1010

int n, x;
vector<int> lose(maxn, 0);
vector<int> win(maxn, 0);
vector<int> use(maxn, 0);
vector<vector<long long>> dp(maxn, vector<long long>(maxn, 0)); // 面对第i个人，自己还剩j个药，往后的最大经验。经验数据太大 要用long long

// 每个人都要打 只是用药或者不用药的区别
long long dfs(int idx, int rest)
{
    if (idx > n)
        return 0;
    if (dp[idx][rest])
        return dp[idx][rest];

    if (rest >= use[idx])
        return dp[idx][rest] = max(dfs(idx + 1, rest) + lose[idx], dfs(idx + 1, rest - use[idx]) + win[idx]);
    return dp[idx][rest] = dfs(idx + 1, rest) + lose[idx];
}

int main()
{
    cin >> n >> x;
    for (int i = 1; i <= n; i++)
        cin >> lose[i] >> win[i] >> use[i];
    cout << 5 * dfs(1, x);
    return 0;
}



// 2. 顺序递推
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define maxn 1010

int n, x;
vector<int> lose(maxn, 0);
vector<int> win(maxn, 0);
vector<int> use(maxn, 0);
vector<long long> dp(maxn, 0);

int main()
{
    cin >> n >> x;
    for (int i = 1; i <= n; i++)
        cin >> lose[i] >> win[i] >> use[i];

    // 与base case和解了
    // 很多情况下base case是0，但没法确定地写出
    // 其实我们只要能保证，如果题目里给出base case是1或其他非0值（如背包恰好填满），我们能识别出来即可
    // 没必要非得跟0过不去
    // 只要dfs里写了return 0，那就直接无脑
    for (int i = 1; i <= n; i++)
    {
        // 这里注意 dp[i][j] = dp[i-1][j]模型不再成立，这里还有lose[i]的影响，因此不能用背包模板写法
        for (int j = x; j >= 0; j--)
        {/*
            if (j >= use[i])
                dp[j] = max(dp[j] + lose[i], dp[j - use[i]] + win[i]);
            else
                dp[j] = dp[j] + lose[i];*/
        }
    }

    //cout << 5 * dp[x];
    return 0;
}