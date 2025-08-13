// 邻接矩阵适用于稠密图
// 缺点是空间复杂度高
// 邻接矩阵访问边的时间复杂度为O(1)。对于边稠密的情况，邻接表的效率会非常低

// 对于无向图，邻接矩阵是对称的。构建时正反两个方向都加边即可
// 这里演示有向图

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10;
int n, m;
int g[N][N];    // 邻接矩阵

int main() {
    cin >> n >> m;

    // 无穷意味着两点直接不可达
    memset(g, 0x3f, sizeof g);
    // 一般情况下，自环为0
    for (int i = 1; i <= n; i++) {
        g[i][i] = 0;
    }

    // 读入边
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        // 对于最短路问题，如果读入重边，更新为最短边
        // 其他问题需要不同的存储逻辑
        g[a][b] = min(g[a][b], w);
    }

    return 0;
}
