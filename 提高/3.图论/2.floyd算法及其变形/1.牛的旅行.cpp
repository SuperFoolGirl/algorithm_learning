// 对于任意两点(牧区)间的最短路
// 其中最远的，称为直径——直径=连通块内最长最短路
// 数据中有若干连通块(牧场)，目标是在任意两个连通块间连一条边
// 新牧场在整个农场(图)中应当有最小直径

// 设目标牧场为A和B，A的直径为d1，B的直径为d2
// 若连接AB，则新牧场直径为d
// 一定有 d >= max(d1, d2)
// 因为新连的边不会影响A,B内部点对的情况；但有可能影响A和B之间的点对的情况
// 对于A-B，其直径为AB所有点中任意两点间最短路的最大值
// 原本A中的i与B中的j不可达；连上边后，它可能可达了，并成为最短路的最大值，即新直径
// 我们要找的就是，使得这个新直径在真个农场中最小的情况

// 假设A-B建边，建在a->b上，那么如何求经过边a->b的直径？
// 很简单，在A中找到到达a的直径，在B中找到到达b的直径，二者相加再加上d(i,j)就是经过a->b的直径了

// 代码：
// 1.floyd求任意两点最短路
// 2.求dmax[i]，表示与i连通且距离i最远的点的距离
// 3.1 所有dmax[i]的最大值
// 3.2 枚举在哪两个点i,j之间连边，条件是不连通；对应直径为dmax[i]+dmax[j]+d[i][j]
// 对3.1和3.2取max

#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int N = 150;
const double INF = 1e20;

int n;
PII q[N];
double d[N][N], dmax[N];
char g[N][N];

void floyd() {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}

double get_dist(PII a, PII b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> q[i].x >> q[i].y;
    }

    for (int i = 0; i < n; i++) {
        cin >> g[i];
    }

    // 初始化距离矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                if (g[i][j] == '1') {
                    d[i][j] = get_dist(q[i], q[j]);
                } else {
                    d[i][j] = INF;
                }
            }
        }
    }

    floyd();

    // 求dmax
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (d[i][j] < INF) {
                dmax[i] = max(dmax[i], d[i][j]);
            }
        }
    }
    // 求dmax的最大值
    double res1 = 0;
    for (int i = 0; i < n; i++) {
        res1 = max(res1, dmax[i]);
    }

    // 枚举连边
    double res2 = INF;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (d[i][j] >= INF) {  // 取>是为了防止double精度问题
                res2 = min(res2, dmax[i] + dmax[j] + get_dist(q[i], q[j]));
            }
        }
    }

    cout << max(res1, res2) << endl;

    return 0;
}
