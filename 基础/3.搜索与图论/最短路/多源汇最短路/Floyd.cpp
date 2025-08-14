// 所谓多源汇，就是可以询问任意两点间的最短路
// 上面的单源汇，都是从一个点出发到其他点的最短路

// 动态规划问题
// d(k, i, j)表示从i到j的最短路径，经过的点只能是1到k
// d(k, i, j) = d(k-1, i, k) + d(k-1, k, j)
// 根据动态规划，状态转移方程与自己取最小值，为
// d(k, i, j) = min(d(k-1, i, j), d(k-1, i, k) + d(k-1, k, j))
// 参数1可以取消，变为
// d(i, j) = min(d(i, j), d(i, k) + d(k, j))

// 可以处理负权边，但无法处理负权环
// 可以存在重边/自环：重边保留最短，自环直接删

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10;

int n, m, k;
int d[N][N];    // 用于存储边，可视为邻接矩阵

void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}

int main() {
    cin >> n >> m >> k;

    // 初始化邻接矩阵
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {    // 删去自环
                d[i][j] = 0;
            } else {
                d[i][j] = 1e9;
            }
        }
    }

    // 输入边
    while (m--) {
        int a, b, w;
        cin >> a >> b >> w;
        d[a][b] = min(d[a][b], w);    // 重边保留最小
    }

    floyd();

    // k次询问
    while (k--) {
        int a, b;
        cin >> a >> b;
        if (d[a][b] > 1e9 / 2) {    // 存在负权边，与BF算法同款处理方式
            cout << "impossible" << endl;
        } else {
            cout << d[a][b] << endl;
        }
    }

    return 0;
}
