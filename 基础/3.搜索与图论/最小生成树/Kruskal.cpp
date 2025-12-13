// 1. 对所有边按照权重进行排序
// 2. 枚举每条边a,b,权重为c。如果ab不连通（ab不在同一集合中），则将其加入最小生成树
// 集合可以用并查集来维护

// 需要排序所有的边，因此适用于稀疏图

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10;
int n, m;
int p[N];

struct Edge {
    int a;
    int b;
    int w;

    // 需要提供比较函数
    bool operator<(const Edge& W) const {
        return w < W.w;
    }
} edges[N];

int find(int x) {
    if (p[x] != x) {    // 只有祖宗节点才满足p[u]=u。如果不是祖宗节点，就继续往上找
        p[x] = find(p[x]);
    }
    return p[x];
}

int kruskal() {
    int res = 0, cnt = 0;    // res存储总边权，cnt存储当前最小生成树里的边数

    // 排序边权
    sort(edges, edges + m);

    // 初始化并查集
    for (int i = 1; i <= n; i++) {
        p[i] = i;
    }

    // 找边来组织最小生成树
    for (int i = 0; i < m; i++) {
        int pa = find(edges[i].a);
        int pb = find(edges[i].b);
        if (pa != pb) {
            p[pa] = pb;           // 合并两个集合
            res += edges[i].w;    // 加入边权
            cnt++;                // 边数加一
        }

        // 如果边数已经达到n-1，说明最小生成树已经构成
        if (cnt == n - 1) {
            break;
        }
    }

    // 如果边数不等于n-1，说明无法构成最小生成树
    if (cnt < n - 1) {
        return -1;
    }
    return res;
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        edges[i] = {a, b, w};
    }

    int t = kruskal();
    if (t == -1) {
        cout << "impossible" << endl;
    } else {
        cout << t << endl;
    }

    return 0;
}
