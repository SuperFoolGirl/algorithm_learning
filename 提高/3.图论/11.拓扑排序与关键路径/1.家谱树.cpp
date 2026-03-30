#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110, M = N * N / 2;  // 最坏情况是完全图，边数为n(n-1)/2

int n;
int h[N], e[M], ne[M], idx;
int q[N];
int d[N];  // 入度

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

void toposort() {
    // 需要将所有入度为0的点入队，因此需要tt=-1，统一出队条件
    int hh = 0, tt = -1;
    for (int i = 1; i <= n; i++) {
        if (!d[i]) {
            q[++tt] = i;
        }
    }

    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (--d[j] == 0) {
                q[++tt] = j;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    memset(h, -1, sizeof h);

    for (int i = 1; i <= n; i++) {
        int t;
        while (cin >> t, t) {
            add(i, t);
            d[t]++;
        }
    }

    toposort();

    // 队列中的数据就是拓扑序
    for (int i = 0; i < n; i++) {
        cout << q[i] << " ";
    }

    return 0;
}
