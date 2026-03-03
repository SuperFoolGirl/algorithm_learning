// 二维费用是一类问题，可以出现在01背包、完全背包、多重背包、分组背包中
// T3就是二维费用问题

// 状态表示 f(i,j,k)
// 集合：表示从前i个物品中选，花费1不超过j，且花费2不超过k的选法集合
// 属性：最值
// 状态计算：枚举第i个物品选或不选两种情况，设费用数组分别为v和m，价值数组为w
// f(i,j,k) = max{ f(i-1,j,k), f(i-1,j-v[i], k-m[i]) + w[i] }

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

int n, V, M;
int f[N][N];  // 降维掉i

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> V >> M;

    for (int i = 0; i < n; i++) {
        // 在DP循环中进行输入是合理的，因为只用到一重滚动数组
        // 这样一来，还省去了存储物品信息的空间
        int v, m, w;
        cin >> v >> m >> w;
        for (int j = V; j >= v; j--) {
            for (int k = M; k >= m; k--) {
                f[j][k] = max(f[j][k], f[j - v][k - m] + w);
            }
        }
    }

    cout << f[V][M] << endl;

    return 0;
}
