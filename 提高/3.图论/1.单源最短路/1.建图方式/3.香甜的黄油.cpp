// 多源汇最短路问题，很适合floyd，但数据量太大了，不允许
// 相当于对所有点做一次单源最短路
// dijkstra: O(n * m log n)
// spfa: O(n * m), 最坏O(n^2 * m)

// 因此就用spfa了

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 810, M = 3000, INF = 0x3f3f3f3f;

int n, p, m;
int id[N];
int h[N], e[M], ne[M], w[N], idx;
int dist[N], q[N];
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

int spfa(int start) {
    // st数组不需要每次清空，因为自然执行结果后会自动全变为false
    memset(dist, 0x3f, sizeof dist);
    dist[start] = 0;
    int hh = 0, tt = 1;
    q[0] = start;
    st[start] = true;

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

    int res = 0;
    for (int i = 0; i < n; i++) {
        int j = id[i];
        // 如果有点不可达，直接返回INF，不要返回多余内容，会干扰判断
        if (dist[j] == INF) {
            return INF;
        }
        res += dist[j];
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> p >> m;
    for (int i = 0; i < n; i++) {
        cin >> id[i];
    }

    memset(h, -1, sizeof h);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);
    }

    int res = INF;
    for (int i = 1; i <= p; i++) {
        // spfa返回所有奶牛所在点到i点距离之和
        res = min(res, spfa(i));
    }

    cout << res << endl;

    return 0;
}
