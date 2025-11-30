// 维护出度，入度两个数组，来实现多源汇的关键路径
// 另外，多源汇代码是兼容单源汇的，前提是维护出度

#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int N = 1e5 + 10, M = 2 * N;
int n, m;
int h[N], e[M], ne[M], w[M], idx;
int in_d[N], out_d[N];
vector<int> earliest(N, 0);
vector<int> latest(N, 1e9);
vector<int> topo_order;
vector<int> sinks;

void add(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

bool topoSort() {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (!in_d[i]) {
            q.push(i);
        }
        if (out_d[i] == 0) {
            sinks.push_back(i);    // 加入汇点
        }
    }

    while (!q.empty()) {
        int t = q.front();
        q.pop();

        topo_order.push_back(t);

        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            in_d[j]--;
            if (in_d[j] == 0) {
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

    // 计算所有事件最早发生时间
    for (int node : topo_order) {
        for (int i = h[node]; i != -1; i = ne[i]) {
            int j = e[i];
            earliest[j] = max(earliest[j], earliest[node] + w[i]);
        }
    }

    // 和单源汇一样，关键路径只需要统计汇点
    // 下面这行代码是对汇点的最晚发生时间初始化
    // latest[ed] = earliest[ed];
    // 但是多源汇中，右值需要取所有汇点中最晚发生的那个时间，也就是最短工期
    int tot_time = 0;
    for (int sink : sinks) {
        tot_time = max(tot_time, earliest[sink]);
    }
    // 求出这个汇点的最晚时间后，统一更新为它
    for (int sink : sinks) {
        latest[sink] = tot_time;
    }

    for (auto it = topo_order.rbegin(); it != topo_order.rend(); ++it) {
        int node = *it;
        for (int i = h[node]; i != -1; i = ne[i]) {
            int j = e[i];
            latest[node] = min(latest[node], latest[j] - w[i]);
        }
    }

    // 输出最短工期
    cout << tot_time << endl;
    // 遍历所有边，输出关键路径
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
        out_d[a]++;
        in_d[b]++;
    }

    if (!criticalPath()) {
        cout << "有环，关键路径不存在" << endl;
    }

    return 0;
}
