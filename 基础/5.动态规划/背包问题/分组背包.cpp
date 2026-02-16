// 分组背包问题
// 给n组物品，每组最多只能选一个物品，求最大价值。i组物品数量为s[i]，每个物品的体积和价值分别为v[i][k]和w[i][k]，背包容量为m
// 状态转移方程思路：枚举第i组选哪个物品
// 1. 不选：f[i][j] = f[i-1][j]
// 2. 选则遍历组内所有物品：f[i][j] = max(f[i-1][j-v[i][k]] + w[i][k])
// 合并分段函数：f[i][j] = max(f[i-1][j], max(f[i-1][j-v[i][k]] + w[i][k]))

// 注意，对于选择的物品本身，依然是01模式；组内的选择通过加了一重循环来实现。整体理解方式还是参考01背包
// 因此，滚动数组优化也是01背包模式，第二层枚举背包容量的循环需要倒置

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10;
int n, m;
int v[N][N], w[N][N], s[N]; // 第一个下标代表组，第二个下标是i组内的第j个物品
int f[N];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> s[i]; // i组物品数量为s[i]
        for (int j = 1; j <= s[i]; j++) {
            cin >> v[i][j] >> w[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 0; j--) {
            for (int k = 1; k <= s[i]; k++) { // 遍历组内所有物品
                if (j >= v[i][k]) {
                    f[j] = max(f[j], f[j - v[i][k]] + w[i][k]);
                }
            }
        }
    }

    cout << f[m] << endl;

    return 0;
}
