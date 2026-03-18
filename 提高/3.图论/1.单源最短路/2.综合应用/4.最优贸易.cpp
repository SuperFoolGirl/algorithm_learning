// 与DP结合

// 题目
// 1.既有无向边，又有有向边
// 2.一个点可以重复经过，只要保证起点是1，终点是n，在这过程中先买再买最多挣多少钱(可以先经过终点而不结束，卖出后再度回到终点)

// 设k为卖出和买入的分界线
// 即1->k->n，买入在k之前，卖出在k之后
// 1->k 买入的最小值：dmin[k]
// k->n 卖出的最大值：dmax[k]
// 1->k->n的最大利润：max(dmax[k]-dmin[k])

// 此处回忆下题意：点可以重复经过，因此只要是能到达k的点，即使是终点，也可以算进来——只要满足图中的可达关系，毕竟图是不完全无向的
// dmin[k]求法：
// 设所有能到达k的点为S1,S2,...,St
// dmin[k] = min{w[k], dmin[S1], dmin[S2],..., dmin[St]}
// 初始状态是dmin[1]=w[1]，其他点由此递推求出
// dmax[k]求法：建反向图，从n号点出发，用类似的方法求得
// dmax[k] = max(w[k], dmax[S1], dmax[S2],..., dmax[St])
// 初始状态是dmax[n]=w[n]，其他点由此递推求出
// 最后求max(dmax[k]-dmin[k])，k从1到n枚举

// 由于本题的图为非拓扑图，因此不能用DP，需要用最短路算法求解
// dijkstra和spfa选哪个呢？
// 根据题意，dijkstra不行。因为在本题中，一个点可能同时出现在方案中多次，即前面说的“先路过终点，卖完再回来”
// 这和dijkstra的贪心选择相违背
// 从这个角度来看，会发现spfa的适用性比dijkstra要好很多

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 100010, M = 2000010;

int n, m;
int w[N];
// hs存储正向图，ht存储反向图
// e/ne数组不需要开两个，idx会区分好不同图的边
int hs[N], ht[N], e[M], ne[M], idx;
int dmin[N], dmax[N];  // 本题是点权，不是边权
bool st[N];
int q[N];

void add(int h[], int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

void spfa(int h[], int dist[], int type) {
    int hh = 0, tt = 1;
    if (type == 0) {
        memset(dist, 0x3f, sizeof dist);
        dist[1] = w[1];  // 点权
        q[0] = 1;
    } else {
        memset(dist, -0x3f, sizeof dist);
        dist[n] = w[n];
        q[0] = n;
    }

    while (hh != tt) {
        int t = q[hh++];
        if (hh == N) {
            hh = 0;
        }
        st[t] = false;

        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (type == 0 && dist[j] > min(dist[t], w[j])) {
                dist[j] = min(dist[t], w[j]);
            }
            if (type == 1 && dist[j] < max(dist[t], w[j])) {
                dist[j] = max(dist[t], w[j]);
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    memset(hs, -1, sizeof hs);
    memset(ht, -1, sizeof ht);
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add(hs, a, b);
        add(ht, b, a);
        if (c == 2) {
            add(hs, b, a);
            add(ht, a, b);
        }
    }

    spfa(hs, dmin, 0);  // 0表示求dmin
    spfa(ht, dmax, 1);  // 1表示求dmax

    int res = 0;
    for (int i = 1; i <= n; i++) {
        res = max(res, dmax[i] - dmin[i]);
    }

    cout << res << endl;

    return 0;
}
