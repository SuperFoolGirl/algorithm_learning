// 每个位置枚举放或者不放，指数型枚举 2^n
// 第一种写法 需要用vis数组
#include <iostream>
using namespace std;
#define maxn 15

int n;
int s[maxn] = {0}, b[maxn] = {0};
int sumS = 1, sumB = 0;
bool vis[maxn] = {false};
int min_num = 0x7fffffff;

void dfs(int x)
{
    if (x == n)
        return;
    for (int i = 1; i <= n; i++)
    {
        if (vis[i] == false)
        {
            vis[i] = true;
            sumS *= s[i];
            sumB += b[i];
            min_num = min(min_num, abs(sumB - sumS));
            dfs(x + 1);
            sumS /= s[i];
            sumB -= b[i];
            vis[i] = false;
        }
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> s[i] >> b[i];
    dfs(0);
    cout << min_num;
    return 0;
}

// 第二种写法 双递归 不需要vis数组
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;
#define maxn 15 // 最大食材数量

int n;
int s[maxn] = {0}, b[maxn] = {0}; // 酸度和苦度
int min_num = INT_MAX;            // 最小绝对差

void dfs(int x, int sumS, int sumB)
{
    if (x == n) // 如果已经枚举完所有食材
    {
        if (sumS != 1 || sumB != 0) // 至少选择一种食材。注意这里不能是&&，否则逻辑就变为了“酸和苦都要发生改变才能进入”
            min_num = min(min_num, abs(sumB - sumS));
        return;
    }

    // 不选择当前食材
    dfs(x + 1, sumS, sumB);

    // 选择当前食材
    dfs(x + 1, sumS * s[x], sumB + b[x]);
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> s[i] >> b[i]; // 输入每种食材的酸度和苦度

    dfs(0, 1, 0);            // 从第 0 种食材开始搜索
    cout << min_num << endl; // 输出最小绝对差
    return 0;
}