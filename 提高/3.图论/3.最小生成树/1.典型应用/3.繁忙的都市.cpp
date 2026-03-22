// 普通的mst，要求树的总边权最小
// 本体的mst，要求最大边权最小

// 最大值最小，一眼二分，右模板
// 枚举最大边权mid，check判断<=mid的边能不能把所有点连通起来
// check部分用bfs/dfs/并查集都行，反正就是判断图的连通性

// 那么用mst算法可解吗？
// 先给结论：kruskal算法保证求出来的mst的最大边权最小
// 证明：kruskal选择的最后一条边，就是mst中最大边权的边；如果不选择它，那么一定会有另一条路径形与它形成环...(参考readme)

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 310, M = 10010;
int n, m;
struct Edge {
    int a, b, w;
    bool operator<(const Edge& t) const {
        return w < t.w;
    }
} e[M];
int p[N]; // 并查集

int find(int x) {
    if (p[x] != x) {
        p[x] = find(p[x]);
    }
    return p[x];
}

int kruskal() {
    int res = 0;  // 记录最大边权
    for (int i = 1; i <= n; i++) {
        p[i] = i;
    }
    sort(e, e + m);

    for (int i = 0; i < m; i++) {
        int a = find(e[i].a), b = find(e[i].b), w = e[i].w;
        if (a != b) {
            p[a] = b;
            res = w;
        }
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> e[i].a >> e[i].b >> e[i].w;
    }

    cout << n - 1 << ' ' << kruskal() << endl;

    return 0;
}
