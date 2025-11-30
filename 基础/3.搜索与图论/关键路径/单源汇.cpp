// 源点是所有入度为0的点的集合，汇点是所有出度为0的点的集合
// 如果确保图是单源汇的，那topo_order的第一个点就是源点，最后一个点就是汇点

// 注意，可能不止有一条关键路径
// 关键路径的找法：遍历所有的边(活动)，符合公式的就是关键活动。相关推导可以回顾。
// 因此，一个点可能有多个关键事件子结点，也就形成了多条关键路径

#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int N = 1e5 + 10, M = 2 * N;
int n, m;
int h[N], e[M], ne[M], w[M], idx;
int d[N];
vector<int> earliest(N, 0);
vector<int> latest(N, 1e9);
vector<int> topo_order;

void add(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

bool topoSort() {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (!d[i]) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int t = q.front();
        q.pop();

        topo_order.push_back(t);

        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            d[j]--;
            if (d[j] == 0) {
                q.push(j);
            }
        }
    }

    return topo_order.size() == n;
}

bool criticalPath() {
    if (!topoSort()) {
        return false;
    }

    for (int node : topo_order) {
        for (int i = h[node]; i != -1; i = ne[i]) {
            int j = e[i];
            earliest[j] = max(earliest[j], earliest[node] + w[i]);
        }
    }

    // 只需要统计汇点
    int ed = topo_order.back();
    latest[ed] = earliest[ed];

    for (auto it = topo_order.rbegin(); it != topo_order.rend(); ++it) {
        int node = *it;
        for (int i = h[node]; i != -1; i = ne[i]) {
            int j = e[i];
            latest[node] = min(latest[node], latest[j] - w[i]);
        }
    }

    // 输出最短工期
    cout << earliest[ed] << endl;
    // 输出关键路径
    for (int node = 1; node <= n; ++node) {
        for (int i = h[node]; i != -1; i = ne[i]) {
            int j = e[i];
            if (earliest[node] == latest[j] - w[i]) {
                cout << node << " -> " << j << endl;
            }
        }
    }

    return true;
}

int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        d[b]++;
    }

    if (!criticalPath()) {
        cout << "有环，关键路径不存在" << endl;
    }

    return 0;
}
