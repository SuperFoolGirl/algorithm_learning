// 单向
// 有重边
// 从给定的起点中任选一个+唯一终点

// 朴素想法：所有起点跑dijkstra。时间太差

// 逃课：建反向边，原终点作为唯一起点
// 但这种方法不易扩展，下面提供通用解法：
// 建立虚拟源点，到真实源点的边权为0
// 注意，需要多开一些边数组大小，为虚拟源点的边留出空间

// 所有多源/多汇问题，在不考虑反向边逃课/floyd的情况下，都可以试着建立虚拟源汇点

// 额外讲一下最短路中的重边问题
// 如果以邻接表建图，那么无需处理重边——松弛过程会自然淘汰边权更大的边，使其不会保留在dist中，进而不对结果产生影响
// 松弛操作本质上就是一个不断取min的过程。重边在算法眼里和普通边没有区别，只是多了一次无效或有效的松弛而已
// 而若是邻接矩阵，就需要自行维护，保留边权更小的边

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1010, M = 21010, INF = 0x3f3f3f3f;

int n, m, T;
int h[N], e[M], ne[M], w[M], idx;
int dist[N], q[N];
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

int spfa() {
    memset(dist, 0x3f, sizeof dist);
    dist[0] = 0;

    int hh = 0, tt = 1;
    q[0] = 0;
    st[0] = true;

    while (hh != tt) {
        int t = q[hh++];
        if (hh == N) {
            hh = 0;
        }
        st[t] = false;

        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                if (!st[j]) {
                    q[tt++] = j;
                    if (tt == N) {
                        tt = 0;
                    }
                    st[j] = true;
                }
            }
        }
    }
    
    if (dist[T] == INF) {
        return -1;
    } else {
        return dist[T];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    while (cin >> n >> m >> T) {
        memset(h, -1, sizeof h);
        idx = 0;

        while (m--) {
            int a, b, c;
            cin >> a >> b >> c;
            add(a, b, c);
        }

        // 输入原源点
        int s;
        cin >> s;
        while (s--) {
            int ver;
            cin >> ver;
            // 创建虚拟源点，0号点
            add(0, ver, 0);
        }

        cout << spfa() << endl;
    }

    return 0;
}
