// 背包问题求具体方案

// 1. map，set教学
// 果不其然，MLE了
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>
#define maxn 1010
using namespace std;

// 存储每个状态对应的选择物品集合
// 解析一下这个嵌套map。我真没想到还能这么用，这就和嵌套vector同理，用二维map去映射set
// 键是int-int，值是set<int>
// 亏我之前还想只能用pair或结构体来进行多参数映射。不过嵌套map肯定多花空间了
unordered_map<int, unordered_map<int, set<int>>> m;
vector<int> v(maxn, 0);
vector<int> w(maxn, 0);
vector<vector<int>> dp(maxn, vector<int>(maxn, 0));
int N, V;

int dfs(int x, int rest)
{
    if (x > N)
        return 0;
    if (dp[x][rest])
        return dp[x][rest];

    if (rest >= v[x])
    {
        int a = dfs(x + 1, rest);
        int b = dfs(x + 1, rest - v[x]) + w[x];

        if (a > b)
        {
            dp[x][rest] = a;
            m[x][rest] = m[x + 1][rest];
        }
        else
        {
            dp[x][rest] = b;
            m[x][rest] = m[x + 1][rest - v[x]];
            m[x][rest].insert(x);
        }
    }
    else
    {
        dp[x][rest] = dfs(x + 1, rest);
        m[x][rest] = m[x + 1][rest];
    }

    return dp[x][rest];
}

int main()
{
    cin >> N >> V;
    for (int i = 1; i <= N; i++)
        cin >> v[i] >> w[i];

    dfs(1, V); // 不需要用返回值，需要的答案在dfs数组的map中。但不代表dfs函数类型是void，因为内部递归需要返回值

    // 输出选择的物品编号
    for (auto i : m[1][V])
        cout << i << " ";

    return 0;
}



// 2. AI思路（只能过数据较少的样例）
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1010;
int dp[MAXN][MAXN];   // dp[i][j] 表示前 i 个物品在背包容量为 j 时的最大价值
int v[MAXN], w[MAXN]; // 物品的体积和价值
bool selected[MAXN];  // 标记物品是否被选择

int main()
{
    int N, V;
    cin >> N >> V;

    // 输入每个物品的体积和价值
    for (int i = 1; i <= N; i++)
        cin >> v[i] >> w[i];

    // 动态规划求解最大价值
    for (int i = 1; i <= N; i++)
    {
        for (int j = 0; j <= V; j++)
        {
            dp[i][j] = dp[i - 1][j];
            if (j >= v[i])
            {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - v[i]] + w[i]);
            }
        }
    }

    // 逆向确定选择方案
    int j = V;
    for (int i = N; i >= 1; i--)
    {
        if (j >= v[i] && dp[i][j] == dp[i - 1][j - v[i]] + w[i])
        {
            selected[i] = true;
            j -= v[i];
        }
    }

    // 正向输出选择结果
    bool first = true;
    for (int i = 1; i <= N; i++)
    {
        if (selected[i])
        {
            if (!first)
            {
                cout << " ";
            }
            cout << i;
            first = false;
        }
    }
    cout << endl;

    return 0;
}



// 3. 顺序递推
// 由于dp数组降维了，map自然也可以降
/*

*/