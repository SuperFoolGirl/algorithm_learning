// 本题题设“没必要用多样东西换一样东西”
// 实际是在说，这就是最短路问题
// 父结点只能挑一个子结点进行转移

// 建图
// 本题最核心的问题，在于设立虚拟源点
// 首先，设1号物品为终点，这很符合逻辑
// 但是，源点是什么呢？
// 根据题意，有非常多的源点——可以直接买1号物品，可以2->1，也可以4->2->1，等等
// 在本题中，由于是联通有向图，因此任何一个点都能到达终点
// 这种情况下，要使用虚拟源点，像集线器一样来“管理”这些大量的真实源点
// 即创建虚拟源点S，直接连接图中所有点
// S->A表示从直接购买A开始，即A是“真实源点”
// 将虚拟源点设为0号点

// 等级限制
// 无法直接体现在图上
// 需要main中枚举等级区间，然后多次求解，最后取最优解
// level[1]必须参与计算，这是终点
// 又因为题设等级差为m，因此最下下界为level[1]-m，最大下界为level[1](保证l1一定在可选范围内 )
// 因此，枚举的区间范围为[level1-m,level1]~[level1,level1+m]
// 只要物品的等级在枚举的区间内，就可以扩展出边，否则不扩展

#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>


#define x first
#define y second

using namespace std;

const int N = 110, INF = 0x3f3f3f3f;

typedef pair<int, int> PII;

int n, m;
int w[N][N], level[N];
int dist[N];

int dijkstra(int l, int r) {
    memset(dist, 0x3f, sizeof dist);
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    // 源点是0
    dist[0] = 0;
    pq.push({0, 0});

    while (pq.size()) {
        auto t = pq.top();
        pq.pop();
        int d = t.x, u = t.y;
        if (d >= dist[u]) {
            continue;
        }

        // 邻接矩阵遍历出边
        // 由于不存在g[x][0]，因此0不会作为出边指向的点
        for (int i = 1; i <= n; i++) {
            // 等级在范围内才能扩展出边
            if (level[i] >= l && level[i] <= r) {
                if (dist[i] > dist[u] + w[u][i]) {
                    dist[i] = dist[u] + w[u][i];
                    pq.push({dist[i], i});
                }
            }
        }
    }

    return dist[1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> m >> n;
    memset(w, 0x3f, sizeof w);
    for (int i = 0; i <= n; i++) {
        w[i][i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        int price, cnt;
        cin >> price >> level[i] >> cnt;
        // 虚拟源点建边，防重边
        w[0][i] = min(w[0][i], price);
        while (cnt--) {
            int id, cost;
            cin >> id >> cost;
            w[id][i] = min(w[id][i], cost);
        }
    }

    int res = INF;
    for (int i = level[1] - m; i <= level[1]; i++) {
        // 枚举区间。i为下界，i+m为上界
        res = min(res, dijkstra(i, i + m));
    }

    cout << res << endl;

    return 0;
}
