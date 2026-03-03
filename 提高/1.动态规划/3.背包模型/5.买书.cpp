// 完全背包问题
// 花费：预算
// 价值：方案数，即说明属性为计数

// 注意，n元全部用来买书，不可剩余
// 因此状态表示f(i,j)表示从前i件物品中选，花费恰好为j的集合
// 属性：计数

// 本题物品只有四件，i维为4

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

int n;
int v[4] = {10, 20, 50, 100};
int f[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < 4; i++) {
        // 唯一可正向枚举——完全背包
        for (int j = v[i]; j <= n; j++) {
            f[j] += f[j - v[i]];
        }
    }

    cout << f[n] << endl;

    return 0;
}
