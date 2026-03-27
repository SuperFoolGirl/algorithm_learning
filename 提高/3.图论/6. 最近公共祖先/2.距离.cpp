// 树中两点的距离，在已知lca的情况下可以快速求解：
// 先预处理出各点到达根结点的距离(其实就是深度)
// 距离 = depth[a] + depth[b] - 2 * depth[lca(a,b)]
// 由于是多次查询，因此最短路算法不适用

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 20010, M = N * 2;

int n, m;
int h[N], e[M], ne[M], w[N], idx;
int p[N];
int st[N];  // st[i]表示i的状态，0表示未访问过，1表示正在访问，2表示访问完成
int dist[N];  // dist[i]表示i到根结点的距离

// 询问相关：res存答案，query存询问；query的参数2用来与res下标建立联系
int res[N];
vector<PII> query[N];  // first存储查询的另一个点，second存储查询编号

void add(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

void dfs(int u, int fa) {
    // dist全部初始化为0，恰好符合根结点的情况
    // 其他自然更新即可，不用松弛的情况下不用考虑初始化差异
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == fa) {
            continue;
        }
        dist[j] = dist[u] + w[i];
        dfs(j, u);
    }
}

int find(int x) {
    if (p[x] != x) {
        p[x] = find(p[x]);
    }
    return p[x];
}

void tarjan(int u) {
    // 当前正在搜索的点是1类，同时也是先根遍历的体现：先处理当前点，在递归子树
    st[u] = 1;

    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        // 如果j从未访问过，则为0类
        if (!st[j]) {
            tarjan(j);
            // 访问完成后，说明以j为根的子树都处理好了，此时把j的祖先设置为u
            // 这样做时符合逻辑的：最终目的是把以u为根的子树全部纳入u所在的集合
            p[j] = u;
        }
    }

    // 遍历所有与u有关的查询，即u<->y的最短路
    for (auto item : query[u]) {
        int y = item.first, id = item.second;
        // 如果y为2类，说明u和y的lca在w链上——也就是y所在集合的代表元
        // 根据readme说明，求距离只发生在1类与2类之间；不必考虑0类，否则反而会重复处理无向边
        if (st[y] == 2) {
            int anc = find(y);
            res[id] = dist[u] + dist[y] - 2 * dist[anc];
        }
    }

    // u已经处理完成了，回溯后执行到这里，要结束其声明了
    st[u] = 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);
    }

    // 读入询问
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        if (a != b) {
            query[a].push_back({b, i});
            query[b].push_back({a, i});
        }

        // 如果a和b相等了，说明距离为0，由res自然初始化为0，无需处理
    }

    // 初始化并查集
    for (int i = 1; i <= n; i++) {
        p[i] = i;
    }

    // 对于无向树，任何一个点都可以当做根结点来处理，因此这里直接从1出发就行了
    // 以1为根结点，预处理所有点距离根结点的距离
    dfs(1, -1);
    tarjan(1);

    for (int i = 0; i < m; i++) {
        cout << res[i] << endl;
    }

    return 0;
}
