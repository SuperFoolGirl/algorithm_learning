// 最小生成树-扩展应用中已经讲过次小生成树了
// 方法是先建立mst，然后在非树边中枚举每条边，加入树中形成环，去掉环中权值最大的边(需要维护环内最大边权和次大边权才能求出严格次小生成树)；在这个过程中维护答案，就能求出次小生成树了
// 本题依然采取这个思路，不过用lca的方式来处理

// 维护d1[][],d2[][]
// d1[i][j]表示i往上跳2^j步的过程中，遇到的最大边权；d2[i][j]表示i往上跳2^j步的过程中，遇到的次大边权
// 关于次大值的维护，之前有使用过；忘记了可以看下本题代码
// 与fa、depth一起在bfs中预处理
// 有了这两个数组，就能求出一条路径上的最大边权和次大边权了;readme中已经详细说明，基于二进制的倍增状态数组可以通过二进制拼凑来覆盖路径上任意两点的状态，因此不要对“二进制跳步”无法覆盖所有情况而担忧——d1、d2一定可以维护好路径上的边权情况

// 回到次小生成树
// 成环之前的路径可以自然地看成两段：x->lca 和 y->lca
// 当加入非树边x-y后，树中会形成一个x-y的环(我们只知道这一对起终点，不妨就用它)——xy的一端刚被接上，而另一端就在其lca处
// 因此，对xy做lca，期间统计其路径上的最大边权和次大边权

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 100010, M = 300010, INF = 1e9;

struct Edge {
    int a, b, w;
    bool used;
    bool operator<(const Edge& t) const {
        return w < t.w;
    }
} edge[M];

int n, m;
int h[N], e[M], ne[M], w[M], idx;
int p[N];
int depth[N], fa[N][17];  // log_2(N)约等于16
int d1[N][17], d2[N][17];
int q[N];

void add(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

int find(int x) {
    if (p[x] != x) {
        p[x] = find(p[x]);
    }
    return p[x];
}

LL kruskal() {
    LL res = 0;
    for (int i = 1; i <= n; i++) {
        p[i] = i;
    }
    sort(edge, edge + m);

    for (int i = 0; i < m; i++) {
        int a = find(edge[i].a), b = find(edge[i].b), w = edge[i].w;
        if (a != b) {
            p[a] = b;
            res += w;
            edge[i].used = true;
        }
    }

    return res;
}

void build() {
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; i++) {
        if (edge[i].used) {
            int a = edge[i].a, b = edge[i].b, w = edge[i].w;
            add(a, b, w);
            add(b, a, w);
        }
    }
}

void bfs() {
    memset(depth, 0x3f, sizeof depth);
    depth[0] = 0, depth[1] = 1;  // 哨兵深度为0，根结点深度为1
    int hh = 0, tt = 0;
    q[0] = 1;  // 所有点都在树中，无向树随便选一个当root即可

    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (depth[j] > depth[t] + 1) {
                depth[j] = depth[t] + 1;
                q[++tt] = j;

                // 预处理fa d1 d2
                fa[j][0] = t;
                d1[j][0] = w[i];
                d2[j][0] = -INF;  // 此时还没有次大边权，设为负无穷便于更新

                for (int k = 1; k <= 16; k++) {
                    int anc = fa[j][k - 1];
                    fa[j][k] = fa[anc][k - 1];

                    // 回忆fa的更新：fa[j][k]是分两步走的，这两步没有交集
                    // 两步为j->anc和anc->fa[anc][k-1]
                    // d1,d2需要维护到整条路径的边权情况，因此需要同时考虑这两步
                    // 在这两步里取最大值
                    // 两个数组会走出四个值，在这四个值里找出前2，更新d1[j][k]和d2[j][k]
                    // 不能排序直接取前2，本题要取严格值，第2必须小于第1
                    d1[j][k] = d2[j][k] = -INF;  // 先初始化，后续更新
                    int dist[4] = {d1[j][k - 1], d2[j][k - 1], d1[anc][k - 1], d2[anc][k - 1]};
                    for (int u = 0; u < 4; u++) {
                        int d = dist[u];
                        if (d > d1[j][k]) {
                            d2[j][k] = d1[j][k];
                            d1[j][k] = d;
                        } else if (d != d1[j][k] && d > d2[j][k]) {
                            d2[j][k] = d;
                        }
                    }
                }
            }
        }
    }
}

int lca(int a, int b, int w) {
    // 存储a和b往上跳的过程中，遇到的最大边权和次大边权
    // 每次调用lca要调用多次，因此用静态数组避免重复开辟
    // cnt每次重置，因此不需要清空dist，会逻辑删除
    static int dist[N * 2];
    int cnt = 0;

    // 参数1为深度大的点，参数2为深度小的点
    if (depth[a] < depth[b]) {
        swap(a, b);
    }

    // 跳到同一层
    for (int k = 16; k >= 0; k--) {
        if (depth[fa[a][k]] >= depth[b]) {
            // 更新a往上跳的过程中，遇到的最大边权和次大边权
            dist[cnt++] = d1[a][k];
            dist[cnt++] = d2[a][k];
            // 注意书写顺序，先记录再更新
            a = fa[a][k];
        }
    }

    // 跳到lca的下一层
    if (a != b) {
        for (int k = 16; k >= 0; k--) {
            if (fa[a][k] != fa[b][k]) {
                // 更新a往上跳的过程中，遇到的最大边权和次大边权
                dist[cnt++] = d1[a][k];
                dist[cnt++] = d2[a][k];
                // 更新b往上跳的过程中，遇到的最大边权和次大边权
                dist[cnt++] = d1[b][k];
                dist[cnt++] = d2[b][k];
                // 依旧注意书写顺序
                a = fa[a][k], b = fa[b][k];
            }
        }
        // 最后再更新一次a和b往上跳的过程中，遇到的最大边权和次大边权
        // 这里只有一条边，因此只取d1即可
        dist[cnt++] = d1[a][0];
        dist[cnt++] = d1[b][0];
    }

    // 统计最大边权和次大边权
    // 依然注意要取严格值，次大边权必须小于最大边权
    // 预处理d1,d2时只保证了每段跳跃(2^k)中最大严格大于次大；但整条路径是由多段跳跃凑成的(也就是二进制拼凑)，因此没法保证整条路径上没有重复权值；因此，这里依然要严格维护最大值和次大值的关系
    int dist1 = -INF, dist2 = -INF;
    for (int i = 0; i < cnt; i++) {
        int d = dist[i];
        if (d > dist1) {
            dist2 = dist1;
            dist1 = d;
        } else if (d != dist1 && d > dist2) {
            dist2 = d;
        }
    }

    // 传入参数w为a-b的边权
    // 现在返回a-b的边权与a-b路径上最大边权的差值
    // 根据上述代码维护，dist2一定严格小于dist1
    if (w > dist1) {
        return w - dist1;
    }
    if (w > dist2) {
        return w - dist2;
    }
    return INF;  // 无法成为次小生成树
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> edge[i].a >> edge[i].b >> edge[i].w;
    }

    // 计算mst
    LL sum = kruskal();

    // 建mst
    build();

    // 预处理depth fa d1 d2
    bfs();

    // 枚举非树边，求次小生成树
    LL res = 1e18;  // 用于LL的INF
    for (int i = 0; i < m; i++) {
        if (!edge[i].used) {
            int a = edge[i].a, b = edge[i].b, w = edge[i].w;
            // lca返回新树边-环内最大边权的差值
            res = min(res, sum + lca(a, b, w));
        }
    }

    cout << res << endl;

    return 0;
}
