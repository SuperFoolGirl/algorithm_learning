// 先介绍一个直径的模板求法(边权均为1)：
// 1.从任意一个点a出发，找到距离它最远的点u
// 2.从u出发，找到距离它最远的点v
// 3.u和v之间的距离即为树的直径
// 这里使用BFS

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 100010, M = 2 * N;

int n, m;
int h[N], e[M], ne[M], idx;
int dist[N];
int q[N];

// 返回距离start最远的点
int bfs(int start) {
    // 注意无向图，start可能会重复访问，因此dist要置为一个永远不合法的值，不能是0
    memset(dist, -1, sizeof dist);
    dist[start] = 0;
    int hh = 0, tt = 0;
    q[0] = start;

    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] == -1) {
                dist[j] = dist[t] + 1;
                q[++tt] = j;
            }
        }
    }

    int res = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] > dist[res]) {
            res = i;
        }
    }

    return res;
}

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
        add(b, a);
    }

    // 设起点为1，距离其最远点为u
    int u = bfs(1);
    // 距离u最远的点为v
    int v = bfs(u);

    // u和v之间的距离即为直径
    cout << dist[v] << endl;

    return 0;
}
