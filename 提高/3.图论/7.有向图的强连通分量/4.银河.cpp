// 之前这类题是差分约束做的，这里用SCC
// 不过依然要涉及不等式链、最长最短路与最小最大值、超级源点等操作
// SCC算法的线性时间复杂度比spfa更稳定，但tarjan的劣势在于空间复杂度较高，许多时候需要二次建图，边数开到二倍+建立新表头，几乎翻了一倍
// 本题求最小值，即最长路

// tarjan并不总是能求解最短路/最长路
// 以本题为例，边权均为非负。且需要找正环；若无正环，求到0号点的最远距离
// 而环一定在SCC中；又因为非负，所以只要SCC中存在正边，那么就一定有正环——除非全0
// 如果环中边权都是0，意味着什么？回顾差分约束，意味着所有点都相等(需要首尾相连构建出不等式链。形如a1>=a2>=a3>=...>=a1)

// 不存在正环 <=> SCC中每条边边权为0 <=> 分量中点相等 <=> 可视为一个点，可以合法缩点
// 然后得到DAG，就可以线性递推求最长路了
// 相比于上一题点权，本题为边权，无需判重边

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

// 需要开新图，边数为2倍
const int N = 100010, M = 600010;

int n, m;
int h[N], hs[N], e[M], ne[M], w[N], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];
int id[N], scc_cnt, sz[N];
int dist[N];

void add(int h[], int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u;
    in_stk[u] = true;

    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        } else if (in_stk[j]) {
            low[u] = min(low[u], dfn[j]);
        }
    }

    if (low[u] == dfn[u]) {
        scc_cnt++;
        int y;
        do {
            stk[top--] = y;
            in_stk[y] = false;
            id[y] = scc_cnt;
            sz[scc_cnt]++;
        } while (y != u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    memset(h, -1, sizeof h);
    memset(hs, -1, sizeof hs);

    // 超级源点
    for (int i = 1; i <= n; i++) {
        add(h, 0, i, 1);
    }

    while (m--) {
        int t, a, b;
        cin >> t >> a >> b;
        if (t == 1) {
            add(h, b, a, 0);
            add(h, a, b, 0);
        } else if (t == 2) {
            add(h, a, b, 1);
        } else if (t == 3) {
            add(h, b, a, 0);
        } else if (t == 4) {
            add(h, b, a, 1);
        } else {
            add(h, a, b, 0);
        }
    }

    // 加入超级源点0后，本题保证连通，因此不用考虑多次tarjan
    tarjan(0);

    bool success = true;  // 是否存在正环

    // 建图，别忘了超级源点已加入
    for (int u = 0; u <= n; u++) {
        for (int i = h[u]; ~i; i = ne[i]) {
            int j = e[i];
            int a = id[u], b = id[j];
            if (a != b) {
                add(hs, a, b, w[i]);
            } else {
                // 此时u,j在同一分量中；如果任一边权为正，说明存在正环
                if (w[i] > 0) {
                    success = false;
                    break;
                }
            }
        }
    }

    if (!success) {
        cout << -1 << endl;
    } else {
        // DAG上求最长路，保证DAG连通，只需要初始化一个起点dist[0] = 0
        // 虽然上个题也用了，但这里还是提一嘴
        // DAG求最短/长路，由于满足拓扑序，可以按DP来做
        // 按拓扑序遍历即可：按拓扑序遍历点，然后遍历其出边
        for (int u = scc_cnt; u >= 0; u--) {
            for (int i = hs[u]; ~i; i = ne[i]) {
                int j = e[i];
                dist[j] = max(dist[j], dist[u] + w[i]);
            }
        }

        // 统计所有点(原图点)到0点最长路之和
        // 注意这里遍历的是SCC编号，即新图的点
        LL res = 0;
        for (int i = 1; i <= n; i++) {
            res += (LL)dist[i] * sz[i];
        }
        cout << res << endl;
    }

    return 0;
}
