// 允许重复经过点、边
// 本题需要扩展到所有的边，因为要计算第k短路，而不是最短路
// 因此需要掌握所有边、路线的情况

// 特殊条件：每条最短路至少包含一条边
// 因为有的数据，起点和终点一样
// 此时输出第k+1短路即可，因为最短路是0

// 根据优先队列的性质
// 终点第k次出队时，就是第k短路了

// 启发函数：
// 当前点a到终点的最短距离，即f[a]=g[a]
// 这怎么求？我们的目的不就是依次求最短路，求到第k短路吗？
// 方法：建反向图，从终点出发求到当前点a的最短路
// 由于需要求终点到每个点的最短路，因此没有终点，一直跑完dijkstra就行
// 数据都在dist数组中
// 这里可能不太好理解，详细讲一下：

// 因此本题需要两个邻接表，h[]、rh[]，分别存正边、反边

#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;
typedef pair<int, PII> PIII;

const int N = 1010, M = 200010;

int n, m, S, T, K;
int h[N], rh[N], e[M], ne[M], w[M], idx;
int dist[N];

void add(int h[], int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

void dijkstra() {
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    pq.push({0, T});
    memset(dist, 0x3f, sizeof dist);
    dist[T] = 0;

    while (pq.size()) {
        auto t = pq.top();
        pq.pop();

        int ver = t.y, d = t.x;
        // 出队判重
        if (d > dist[ver]) {
            continue;
        }

        for (int i = rh[ver]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[ver] + w[i]) {
                dist[j] = dist[ver] + w[i];
                pq.push({dist[j], j});
            }
        }
    }
}

int astar() {
    // 堆维护的状态：{估计到终点的距离,与起点的真实距离,当前点}
    priority_queue<PIII, vector<PIII>, greater<PIII>> pq;
    pq.push({dist[S], {0, S}});

    int cnt = 0;  // 记录出队次数
    while (pq.size()) {
        auto t = pq.top();
        pq.pop();

        int ver = t.y.y, d = t.y.x;
        // 终点判断
        if (ver == T) {
            cnt++;
            if (cnt == K) {
                return d;
            }
        }

        for (int i = h[ver]; ~i; i = ne[i]) {
            int j = e[i];
            // 根据题意，需要把所有边都加进来
            // 没有松弛部分了
            pq.push({d + w[i] + dist[j], {d + w[i], j}});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    memset(h, -1, sizeof h);
    memset(rh, -1, sizeof rh);

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(h, a, b, c);
        add(rh, b, a, c);
    }

    cin >> S >> T >> K;

    if (S == T) {
        K++;
    }

    // 反向dijkstra求启发函数
    dijkstra();

    cout << astar() << endl;

    return 0;
}
