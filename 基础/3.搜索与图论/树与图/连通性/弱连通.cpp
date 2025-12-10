// 将有向图的边视为无向边，得到漠视图，若图是连通的，则满足弱连通性
// 弱连通性就是常规连通块问题

// 如果要求满足弱连通性所需要的最小边，那么找生成树即可
// 生成树就是最小的连通子图

// 判断弱连通性：
// 1. dfs：选择任意一个点来dfs，如果能遍历完所有点，则连通，否则不连通；dfs可求出连通块个数
// 2. 生成树：如果没有生成树，说明图必然不连通。但是注意，判断边数时，依赖于图中连通块个数
//    如果整个图由两棵生成树构成，那图中总边数为n-2

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>


using namespace std;

const int N = 1e5 + 10, M = N;

// 用于构建支撑树
struct Edge {
    int a;
    int b;
};

int n, m;
int p[N];
int h[N], e[M], ne[M], idx;
bool vis[N];
vector<Edge> spanning_tree;
vector<Edge> edges;

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

int find(int x) {
    if (x != p[x]) {
        p[x] = find(p[x]);
    }
    return p[x];
}

void dfs(int x, int& cnt) {
    vis[x] = true;
    cnt++;

    for (int i = h[x]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!vis[j]) {
            dfs(j, cnt);
        }
    }
}

bool spanningTree() {
    int cnt = 0;

    for (int i = 1; i <= n; ++i) {
        p[i] = i;
    }

    for (auto& edge : edges) {
        int pa = find(edge.a);
        int pb = find(edge.b);
        if (pa != pb) {
            p[pa] = pb;
            spanning_tree.push_back(edge);
            cnt++;
        }

        if (cnt == n - 1) {
            break;
        }
    }

    return cnt == n - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    memset(h, -1, sizeof h);
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        add(a, b);
        add(b, a);
        edges.push_back({a, b});
    }

    // 判断弱连通性
    int cnt = 0;
    dfs(1, cnt);    // 默认顶点从1开始
    if (cnt != n) {
        cout << "不连通" << endl;
    } else {
        cout << "连通" << endl;
    }

    // 求支撑树
    if (spanningTree()) {
        cout << "连通，生成树已存储" << endl;
    } else {
        cout << "不连通" << endl;
    }

    return 0;
}
