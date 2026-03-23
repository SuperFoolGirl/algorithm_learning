// 题目分析
// 1.所有村庄都要被连接，作为一个大连通块——生成树
// 2.当d确定时，各村庄与连通块的距离必须<=d，才能被连接——因此d是最小生成树上的最大边。如果d太小的话，会导致所有村庄不一定都连通，形成生成森林
// 3.本题还有卫星设备，用于消除大权边。当d过小而形成生成森林时，假设有3个连通块，那么则需要k=3才能把这3个块连起来——还是视块为点的思想
// 总结：找一个最小的d值，使得将所有权值大于d的边删去后，整个图形的连通块个数不超过k(当然，根据题目描述，也可以二分，二分d时check用bfs/dfs/并查集求连通块个数)

// kruskal求连通块本质：
// 处理所有排序好的边时，假设当前已经处理完第i条边，说明已经求出了由前i条边构成的所有连通块；那么，当处理完所有边时，说明求出了由所有点构成的连通块，即最小生成树
// 注意，抛开求mst的视角，而是用求构成连通块的视角来看待kruskal算法，这是其在求mst时的中间产物

// 首先给出本题的感性认识：
// k和d是成负相关的：d是mst的最大边，也就是kruskal每轮循环选中边的边权。没有选边时，所有点都是连通块；随着d增大，连通的点越多，连通块k越少
// 我们需要做的，就是在枚举d的时候，找到第一次使得连通块<=k的d值，即为答案
// 代码：
// 1.边排序
// 2.依次所有边，不断更新连通块，直到连通块<=k，输出当前边权d

#include <algorithm>
#include <cstring>
#include <iostream>
#include <cmath>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int N = 510, M = N * N / 2;

struct Edge {
    int a, b;
    double w;

    bool operator<(const Edge& t) const {
        return w < t.w;
    }
} e[M];

int n, k, m;
PII q[N];    // 存储所有点
int p[N];

int find(int x) {
    if (p[x] != x) {
        p[x] = find(p[x]);
    }
    return p[x];
}

double get_dist(PII a, PII b) {
    int dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

double kruskal() {
    int cnt = n;  // 初始化当前连通块个数，即k
    double res = 0;  // 记录当前边权，即d
    for (int i = 1; i <= n; i++) {
        p[i] = i;
    }
    sort(e, e + m);

    for (int i = 0; i < m; i++) {
        if (cnt <= k) {
            break;
        }

        int a = find(e[i].a), b = find(e[i].b);
        double w = e[i].w;
        if (a != b) {
            p[a] = b;
            cnt--;
            res = w;
        }
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> q[i].x >> q[i].y;
    }

    // 边的数据由坐标算出，注意只需要单向边，不要重复输入
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            e[m++] = {i, j, get_dist(q[i], q[j])};
        }
    }

    cout << kruskal() << endl;

    return 0;
}
