// 生成一个长度为 n 的排列，并找到第 m 个排列后输出
#include <iostream>
using namespace std;

int n, m, ans = 0;
int arr[10005] = {0};
bool st[10005] = {false};
int mars[10005] = {0};

void dfs(int x)
{
    if (ans > m + 1)
        return; // 退出出口

    if (x == n)
    {
        ans++;
        if (ans == m + 1)
        {
            for (int i = 0; i < n; i++)
                cout << arr[i] << ' ';
        }
        return;
    }

    for (int i = 1; i <= n; i++)
    {
        // 如果 ans == 0，表示当前是第一次生成排列，强制从 mars[x] 的值开始生成
        if (ans == 0)
            i = mars[x]; // x代表现在所处的n序列中的位置

        if (st[i] == false)
        {
            st[i] = true;
            arr[x] = i; // 存储当前数字
            dfs(x + 1);
            st[i] = false;
            // arr[x] = 0;
        }
    }
}

int main()
{
    cin >> n >> m;

    // 输入初始序列 mars，用于从某个特定的排列开始生成
    for (int i = 0; i < n; i++)
        cin >> mars[i];

    dfs(0);
    return 0;
}
