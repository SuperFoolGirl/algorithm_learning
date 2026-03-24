// 题目背景：能否回到原来的起点
// 本题中，时间是边权
// 虫洞的作用是时间倒流
// 因此，如果存在一个负环，走下去就可以保证能一直“时间倒流”

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 510, M = 5210;

int n, m1, m2;
int h[N], e[M], ne[M], w[M], idx;
int dist[N];
int q[N], cnt[N];  // cnt[i]表示以i为终点的最短路径经过的边数
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

bool spfa() {
    int hh = 0, tt = 1;
    memset(dist, 0, sizeof dist);  // 距离全为0
    memset(st, 0, sizeof st);
    memset(cnt, 0, sizeof cnt);

    // 全部入队
    for (int i = 1; i <= n; i++) {
        q[tt++] = i;  // 这里一定不会越界，q的大小是上限
        st[i] = true;
    }

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
                cnt[j] = cnt[t] + 1;

                if (cnt[j] >= n) {
                    return true;
                }

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

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m1 >> m2;
        memset(h, -1, sizeof h);
        idx = 0;

        // 建双向边
        for (int i = 0; i < m1; i++) {
            int a, b, w;
            cin >> a >> b >> w;
            add(a, b, w);
            add(b, a, w);
        }
        // 建虫洞，虫洞的作用是让距离变短，因此边权为负数
        for (int i = 0; i < m2; i++) {
            int a, b, w;
            cin >> a >> b >> w;
            add(a, b, -w);
        }

        if (spfa()) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
