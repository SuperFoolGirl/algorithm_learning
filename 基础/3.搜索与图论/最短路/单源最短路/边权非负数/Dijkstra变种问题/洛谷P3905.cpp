// 注意，这题是无向图
// dijkstra剪枝可以自然规避无向图带来的回头
// 除了第一次出队，其他情况下都会被continue剪枝掉

#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

const int N = 110, M = N * N / 2;

typedef pair<int, int> PII;

int h[N], e[M], ne[M], w[M], idx;
int n, m;
int A, B;
int d[N];
bool flag[N][N];

void add(int a, int b, int c) {
    e[++idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx;
}

// 并非传统找最短路
// 松弛指标是：尽量少走炸掉的路，使修路开销最小
// 因此，d用来维护修路长度
int dijkstra() {
    memset(d, 0x3f, sizeof d);
    d[A] = 0;
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    pq.push({0, A});

    while (!pq.empty()) {
        auto t = pq.top();
        pq.pop();

        int dist = t.first, node = t.second;

        if (node == B) {
            return dist;
        }

        if (dist > d[node]) {
            continue;
        }

        for (int i = h[node]; i; i = ne[i]) {
            int j = e[i];
            // 看这条路是不是被炸了
            // 如果炸了，w[i]要加上
            // 如果没炸，直接沿用dist
            if (flag[node][j]) {
                if (d[j] > dist + w[i]) {
                    d[j] = dist + w[i];
                    pq.push({d[j], j});
                }
            } else {
                if (d[j] > dist) {
                    d[j] = dist;
                    pq.push({d[j], j});
                }
            }
        }
    }
    return d[B];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);
    }

    int d;
    cin >> d;
    while (d--) {
        int a, b;
        cin >> a >> b;
        flag[a][b] = true;
        flag[b][a] = true;
    }

    cin >> A >> B;
    int res = dijkstra();

    cout << res << endl;
    return 0;
}
