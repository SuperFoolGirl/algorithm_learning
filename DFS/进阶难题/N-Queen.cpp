// 1 深基
#include <cstdio>
#include <iostream>
using namespace std;
#define maxn 100

int a[maxn] = {0}, n, ans = 0;
int b1[maxn] = {0};     // 标记列是否被占用
int b2[2 * maxn] = {0}; // 标记副对角线（左低右高）是否被占用
// 注意处理负下标的方法。我居然用了map 纯纯小丑
int b3[2 * maxn] = {0}; // 标记主对角线（左高右低）是否被占用

void dfs(int x)
{
    if (x > n)
    {
        ans++; // 找到一个合法方案
        return;
    }

    // x是行，i是列
    for (int i = 1; i <= n; i++) // 并非遍历整个二维数组 而是只遍历行 在每个行里找符合条件的位置。遍历整个二维数组是我的思维定势
    {
        // 检查当前列、副对角线和主对角线是否被占用
        if (b1[i] == 0 && b2[x + i] == 0 && b3[x - i + n] == 0)
        {
            a[x] = i;                              // 记录当前行皇后所在的列。很巧妙，而我居然又想用map。。
            b1[i] = b2[x + i] = b3[x - i + n] = 1; // 标记占用
            dfs(x + 1);                            // 递归放置下一行的皇后
            b1[i] = b2[x + i] = b3[x - i + n] = 0; // 回溯，取消标记
        }
    }
}

int main()
{
    scanf("%d", &n);
    dfs(1);
    printf("%d", ans); // 输出合法方案的数量
    return 0;
}



// 2 洛谷1219
// 3个点TLE
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define maxn 15

int n;
vector<int> row;
bool col[maxn] = {false};
bool main_diag[2 * maxn] = {false};
bool vice_diag[2 * maxn] = {false};
int ans = 0;
vector<vector<int>> ANS;

void dfs(int x)
{
    if (x > n) // 一般来说，dfs传参为0取==，为1取>
    {
        ans++;
        ANS.push_back(row);
        return;
    }

    for (int i = 1; i <= n; i++)
    {
        if (!col[i] && !main_diag[x - i + n] && !vice_diag[x + i])
        {
            row.push_back(i);
            col[i] = main_diag[x - i + n] = vice_diag[x + i] = true;
            dfs(x + 1);
            row.pop_back();
            col[i] = main_diag[x - i + n] = vice_diag[x + i] = false;
        }
    }
}

int main()
{
    cin >> n;
    dfs(1);
    sort(ANS.begin(), ANS.end());
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < n; j++)
            cout << ANS[i][j] << ' ';
        cout << endl;
    }
    cout << ans;
    return 0;
}



// 3 洛谷2105
#include <iostream>
#include <algorithm>
using namespace std;
#define maxn 20010

int main()
{
    int n, m, k;
    int ans = 0;
    bool row[maxn] = {false};
    bool col[maxn] = {false};
    bool diag1[2 * maxn] = {false};
    bool diag2[2 * maxn] = {false};
    cin >> n >> m >> k;
    int a, b;
    int offset = max(m, n);
    for (int i = 0; i < k; i++)
    {
        cin >> a >> b;
        row[a] = true;
        col[b] = true;
        diag1[a - b + offset] = true;
        diag2[a + b] = true;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (!row[i] && !col[j] && !diag1[i - j + offset] && !diag2[i + j])
                ans++;
        }
    }
    cout << ans;
    return 0;
}
