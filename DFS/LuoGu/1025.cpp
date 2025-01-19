// 有序排列 用start
// 注意优化

#include <iostream>
using namespace std;

int n, k, ans = 0;

void dfs(int x, int start, int sum)
{
    if (x == k)
    {
        if (sum == n)
            ans++;
        return;
    }
    // 这里可以优化一下：当还有k-x个元素需要选时，如果全都选最小的依然会超过n，那就没必要再进行了
    for (int i = start; i <= (n - sum) / (k - x); i++)
    {
        if (sum + i <= n)
            dfs(x + 1, i, sum + i);
    }
}

int main()
{
    cin >> n >> k;
    dfs(0, 1, 0);
    cout << ans;
    return 0;
}