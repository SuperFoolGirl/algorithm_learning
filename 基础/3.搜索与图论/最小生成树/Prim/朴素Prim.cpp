// 最小生成树是一个连通块，用集合S来维护在连通块里的点
// 先把所有点到集合的距离初始化为正无穷
// 遍历所有点，找到集合外距离最近的点t加入集合，然后用t更新其他点到集合的距离。这一步是迭代所有点的。
// 每两个点都会比一次的，每次加入新的点，集合外的点都要根据这个点来更新到集合的最短距离
// 所有点加入集合时用到的边，构成了生成树

// 所谓“到集合的距离”，就是外部点有没有一条边能连到集合里的点。我们要取这里面长度最小的一条边

// 根据上面的算法阐释，第一个点是随意找的，所有点都在集合外。为了方便可以取1号点

// 回忆离散数学做法：从任意一个点出发，找到不构成环的最小边，直到所有点都在一个连通块里

// 在算法实现上，类似Dijkstra

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10, INF = 0x3f3f3f3f;
int n, m;
int g[N][N];    // prim适用于稠密图，而邻接矩阵就适用于稠密图
int dist[N];
bool st[N];

int prim() {
    memset(dist, 0x3f, sizeof dist);

    int res = 0;                          // 记录最小生成树中的总边权
    for (int i = 0; i < n; i++) {         // n个点都要加进来
        int t = -1;                       // 当前要加入集合的点
        for (int j = 1; j <= n; j++) {    // 遍历所有集合外的点，从1开始
            // 该点不在集合内，且为第一次查询 或 是当前已知的最近点（打擂台）
            if (!st[j] && (t == -1 || dist[j] < dist[t])) {
                t = j;
            }
        }

        // 如果不是第一个点的情况下，加入进来的点到集合的距离是正无穷，说明图不连通，无法构成生成树
        if (i && dist[t] == INF) {
            return INF;
        }

        // 第一个点到集合的距离是无穷，不予添加进最小生成树的总权。
        // 注意这段代码必须在下面的更新距离之前，否则遇到负权环会出错。
        if (i) {
            res += dist[t];
        }

        // 更新其他点到集合的距离
        for (int j = 1; j <= n; j++) {
            dist[j] = min(dist[j], g[t][j]);    // 这里和Dijkstra有差异
        }

        // 标记进入集合
        st[t] = true;
    }
    return res;
}

int main() {
    cin >> n >> m;
    memset(g, 0x3f, sizeof g);

    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        // 无向图加两次，重边取最小值
        g[a][b] = g[b][a] = min(g[a][b], c);
    }

    int t = prim();    // 返回最小生成树的最小总边权

    if (t == INF) {
        cout << "impossible" << endl;
    } else {
        cout << t << endl;
    }

    return 0;
}
