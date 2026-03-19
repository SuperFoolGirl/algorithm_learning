// 同时维护最短路劲和次短路径的数量
// 本题可以考虑扩展状态表示，而不再引入更多数组
// d[i][0/1] 表示到达节点i的最短路/次短路长度
// cnt[i][0/1] 表示到达节点i的最短路/次短路数量

// d[i][0]和cnt[i][0]上道题已经讲过了，这里主要讲d[i][1]和cnt[i][1]的更新
// 具体逻辑写在代码中了，详见代码吧；显然，d[i][1]和cnt[i][1]的更新也是依赖递推，即拓扑序的

// 上题用BFS，本题需要用Dijkstra了；对于队列来说，正常Dijkstra需要存两个状态，本题中状态表示多了一维，因此需要三个

#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 1010, M = 10010;

struct Ver {
    int ver, type, dist;
    // Dijkstra是大根堆，需要重载>
    bool operator>(const Ver& other) const {
        return dist > other.dist;
    }
};

int n, m, S, T;
int h[N], e[M], ne[M], w[M], idx;
int d[N][2], cnt[N][2];
bool st[N][2];

void add(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

int dijkstra() {
    memset(st, 0, sizeof st);
    memset(d, 0x3f, sizeof d);
    memset(cnt, 0, sizeof cnt);
    d[S][0] = 0;
    cnt[S][0] = 1;

    priority_queue<Ver, vector<Ver>, greater<Ver>> heap;
    heap.push({S, 0, 0});

    while (heap.size()) {
        Ver t = heap.top();
        heap.pop();

        int ver = t.ver, type = t.type, dist = t.dist, count = cnt[ver][type];
        if (st[ver][type]) {
            continue;
        }
        st[ver][type] = true;

        for (int i = h[ver]; ~i; i = ne[i]) {
            int j = e[i];

            // 小于的情况依然不需要讨论，这是松弛方程决定的
            if (d[j][0] > dist + w[i]) {  // 最小值可更新
                // 次小值更新
                d[j][1] = d[j][0];    // 当前的最小值不再是d[j][0]，沦为次小值
                cnt[j][1] = cnt[j][0];  // 次小值的方案数也要更新为原来最小值的方案数
                heap.push({j, 1, d[j][1]});
                // 最小值更新
                d[j][0] = dist + w[i];
                cnt[j][0] = count;
                heap.push({j, 0, d[j][0]});
            } else if (d[j][0] == dist + w[i]) {
                // 最小值和次小值无需更新，但最小值方案增加
                cnt[j][0] += count;
            } else if (d[j][1] > dist + w[i]) {  // 次小值可更新
                // 注意，到达这个循环，说明dist+w[i] > d[j][0]了，因此它只能更新次小值了
                d[j][1] = dist + w[i];
                cnt[j][1] = count;
                heap.push({j, 1, d[j][1]});
            } else if (d[j][1] == dist + w[i]) {
                // 次小值无需更新，但次小值方案增加
                cnt[j][1] += count;
            }
        }
    }

    int res = d[T][0];
    if (d[T][0] + 1 == d[T][1]) {
        res += d[T][1];
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int k;
    cin >> k;
    while (k--) {
        cin >> n >> m;
        memset(h, -1, sizeof h);
        idx = 0;

        while (m--) {
            int a, b, c;
            cin >> a >> b >> c;
            add(a, b, c);
        }

        cin >> S >> T;
        cout << dijkstra() << endl;
    }

    return 0;
}
