// 次小生成树
// 定义：
// 给一个有权图，把图的所有生成树按权值从小到大排序，第二小的称为次小生成树(权值必须严格小于mst，因为可能存在多个mst)
// 求法1(无法求严格次小生成树)
// 先求mst，然后枚举删去mst中的边，再剩余的边中找出一条边加入，枚举n-1次。
// 时间复杂度: O(mlogm + n*m)，后续枚举不再需要排序
// 求法2(可求严格次小生成树)
// 先求mst，然后枚举非mst中的边，然后将该边加入树中，同时从树中去掉一条边，使得维持树的性质(加边后成环，去掉这个环里任意一条边都可以破环；但其实，去掉权值最大的一条边，才有可能成为答案)；枚举m-n+1次的过程中维护答案，就能求出来次小生成树
// 时间复杂度: 删边操作涉及“求树上任意两点间的极值”，简单搜索即可；这部分预处理解决，因此总复杂度为O(n^2 +
// mlogm)，n^2为任意两点间的最大边权
// 总的来说，方法2更优一些

// 代码：
// 1.求mst，统计标记树边和非树边，记mst总边权为sum
// 2.预处理任意两点(a,b)间最大边权dist[a][b]
// 3.依次枚举非树边w，求min{sum+w-dist[a][b]}，其中w>dist[a][b](若无该限制，可能会取等，导致求不到严格次小生成树)

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 510, M = 10010, INF = 1e18;

struct Edge {
    int a, b, w;
    bool f;  // 标记是否为树边
    bool operator<(const Edge& t) const {
        return w < t.w;
    }
} edge[M];

int n, m;
int p[N];
int dist[N][N];
// 需要重新建图，因此需要邻接表
// 新图为树，考虑到是无向边，因此边数开到N*2
int h[N], e[N * 2], ne[N * 2], w[N * 2], idx;

int find(int x) {
    if (p[x] != x) {
        p[x] = find(p[x]);
    }
    return p[x];
}

void add(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

LL kruskal() {
    LL res = 0;
    sort(edge, edge + m);
    for (int i = 1; i <= n; i++) {
        p[i] = i;
    }

    for (int i = 0; i < m; i++) {
        int a = edge[i].a, b = edge[i].b, w = edge[i].w;
        int pa = find(a), pb = find(b);
        if (pa != pb) {
            p[pa] = pb;
            res += w;
            edge[i].f = true;  // 标记树边
            add(a, b, w);
            add(b, a, w);
        }
    }

    return res;
}

// max_d: 记录路径上的最大边权
// d: 记录任意两点间的最大边权，将二维数组按循环一维传参
void dfs(int u, int fa, int max_d, int d[]) {
    d[u] = max_d;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j != fa) {
            dfs(j, u, max(max_d, w[i]), d);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; i++) {
        cin >> edge[i].a >> edge[i].b >> edge[i].w;
    }

    LL sum = kruskal();

    // 预处理任意两点间最大边权
    for (int i = 1; i <= n; i++) {
        // 无向边，需要传入父结点避免重复访问
        dfs(i, -1, 0, dist[i]);
    }

    // 枚举非树边，求答案
    LL res = INF;
    for (int i = 0; i < m; i++) {
        if (!edge[i].f) {
            int a = edge[i].a, b = edge[i].b, w = edge[i].w;
            if (w > dist[a][b]) {
                res = min(res, sum + w - dist[a][b]);
            }
        }
    }

    cout << res << endl;

    return 0;
}
