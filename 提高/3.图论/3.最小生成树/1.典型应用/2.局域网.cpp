// 这里提一句，最小生成树算法是建立在无向图上的
// 本题背景一眼mst

// 题意
// 图无重边无自环
// 去除环和多余的边，使之最后剩下mst
// 那其实直接求mst，然后得到互斥答案即可

// 注意，题目没有说图连通
// 因此，需要在每个连通块内求mst，相当于求“最小生成森林”

// prim算法一次只能处理一个连通块，因此本题用kruskal
// kruskal求最小生成森林的正确性证明：见第四题，有两种理解方式

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110, M = 210;

int n, m;
struct Edge {
    int a, b, w;
    bool operator<(const Edge& t) const {
        return w < t.w;
    }
} e[M];
int p[M]; // 并查集

// 用树自底向上的视角来看find函数，比较好理解
int find(int x) {
    if (p[x] != x) {
        p[x] = find(p[x]);
    }
    return p[x];
}

int kruskal() {
    int res = 0;  // 记录互斥答案

    for (int i = 1; i <= n; i++) {
        p[i] = i;
    }

    sort(e, e + m);

    for (int i = 0; i < m; i++) {
        int a = find(e[i].a), b = find(e[i].b), w = e[i].w;
        if (a != b) {
            p[a] = b;
        } else {
            res += w;
        }
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    
    for (int i = 0; i < m; i++) {
        cin >> e[i].a >> e[i].b >> e[i].w;
    }

    cout << kruskal() << endl;

    return 0;
}
