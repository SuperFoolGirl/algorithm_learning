// 每件物品只能用一次
// 物品给定参数V和W，分别表示体积和价值
// 求在不超过总容量的情况下，包里能装下的最大价值

// 状态表示：i表示前i件物品，j表示当前背包容量
// 状态f(i,j)表示前i件物品中，能够装入容量为j的背包中的最大价值

// 状态计算：将集合f(i,j)划分为两个：
// 1. 第i件物品被选择：f(i-1,j-V[i]) + W[i]
// 2. 第i件物品不被选择：f(i-1,j)
// 这两种情况里面，更大者成立
// 则状态转移方程：f(i,j) = max(f(i-1,j-V[i]) + W[i], f(i-1,j))

// 重点：两种情况中，第二种必然存在，但第一种不一定存在
// 当V[i] > j时，整个背包都放不下它一个，第一种情况就不存在
// 这也就是的代码循环内的逻辑

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10;

int n, m;
int v[N], w[N];
int f[N][N];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> v[i] >> w[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            // 状态转移方程有两种情况，其成立条件各不相同，这里要进行区分
            f[i][j] = f[i - 1][j];    // 情况2一定成立
            if (j >= v[i]) {          // 情况1在该条件下成立
                f[i][j] = max(f[i][j], f[i - 1][j - v[i]] + w[i]);
            }
        }
    }

    cout << f[n][m] << endl; // 输出由题意导出的结果

    return 0;
}
