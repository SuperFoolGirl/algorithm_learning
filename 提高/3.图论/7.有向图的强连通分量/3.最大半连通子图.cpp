// 半连通分量：对于图上任意u,v，存在u->v或v->u的一条路径
// 导出子图：在原图中选择一些点，只保留这些点之间的边，得到的子图叫导出子图

// 有向图为G，求最大半连通(导出)子图G'。“最大”指包含的点数最多
// 输出G'的节点数目K，以及G'的数量C(可能有多个最大半连通子图)

// 想一下，其实一条链就满足半连通的条件了，我们只需要找到最长的链即可；链是作为骨干存在于半连通图中的，对于各种花式的半连通图，应当都能抽出这个骨干
// 链上不允许分叉，否则分叉两端的点之间不满足可达关系
// 对于原图，先执行tarjan转为DAG，然后在新图上统计最长路径，点权为每个SCC包含的点数；DAG求最长路是线性的
// 转为DAG后，满足了拓扑序；又要统计方案数——DP很自然地浮现出来了，f记录最长路长度，g记录最长路方案数

// 注意，两点间可能会有重边；根据导出子图定义，如果选了这两点，那么期间的若干重边必须都选上
// 但其实，对于题目求解的数据而言，逻辑上只有一条就可以了
// 因此，建图时需要对重边进行判重，避免导致错误

#include <algorithm>
#include <cstring>
#include <iostream>
#include <unordered_set>

using namespace std;

typedef long long LL;

const int N = 100010, M = 2000010;

int n, m, mod;
int h[N], hs[N], e[M], ne[M], idx;    // 本题需要彻底建出来新图
int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];
int id[N], scc_cnt, sz[N];
int f[N], g[N];

void add(int h[], int a, int b) {
    e[idx] = b;
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

    cin >> n >> m >> mod;
    memset(h, -1, sizeof h);
    memset(hs, -1, sizeof hs);

    while (m--) {
        int a, b;
        cin >> a >> b;
        add(h, a, b);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    // 缩点建新图，需要给边判重——两点之间只能加边一次，排除可能的重边
    unordered_set<LL> S;
    for (int u = 1; u <= n; u++) {
        for (int i = h[u]; ~i; i = ne[i]) {
            int j = e[i];
            // 一个简单的哈希函数
            LL hash = id[u] * 1000000ll + id[j];
            if (id[u] != id[j] && !S.count(hash)) {
                S.insert(hash);
                add(hs, id[u], id[j]);
            }
        }
    }

    // 用DAG做DP
    // 拓扑序按scc_cnt递减
    for (int i = scc_cnt; i >= 1; i--) {
        // 没有更新过，则为起点；DAG不保证连通，因此可能有多个起点
        // 这里可以视为DP初始化，但是常规DP是连通DAG，只有一个起点
        // 本题为点权，sz做点权数组
        if (!f[i]) {
            f[i] = sz[i];
            g[i] = 1;
        }

        for (int j = hs[i]; ~j; j = ne[j]) {
            int k = e[j];
            // 最长路
            if (f[k] < f[i] + sz[k]) {
                f[k] = f[i] + sz[k];
                g[k] = g[i];
            } else if (f[k] == f[i] + sz[k]) {
                g[k] = (g[k] + g[i]) % mod;
            }
        }
    }

    // 统计最长路长度和方案数
    int maxf = 0, sum = 0;
    for (int i = 1; i <= scc_cnt; i++) {
        if (f[i] > maxf) {
            maxf = f[i];
            sum = g[i];
        } else if (f[i] == maxf) {
            sum = (sum + g[i]) % mod;
        }
    }

    cout << maxf << endl << sum << endl;

    return 0;
}
