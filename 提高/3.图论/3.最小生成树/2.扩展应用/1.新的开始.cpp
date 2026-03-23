// 虚拟源点与最小生成树

// 本题的难点在于，既有点权，又有边权
// 边权是最常用的。如何能把所有点权转化为边权呢？
// 方案：引入一个虚拟源点s，连接所有节点i，边权为点权w[i]
// 因此，转为“求n+1个点的最小生成树”问题

// 本题给出邻接矩阵，因此用prim算法

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 310;

int n;
int w[N][N];
int dist[N];
bool st[N];

int prim() {
    int res = 0;
    memset(dist, 0x3f, sizeof dist);
    dist[0] = 0;  // 虚拟源点到自己的距离为0，第一轮一定会选择它进入mst

    // 共n+1个点，从0开始
    for (int i = 0; i <= n; i++) {
        int t = -1;
        for (int j = 0; j <= n; j++) {
            if (!st[j] && (t == -1 || dist[t] > dist[j])) {
                t = j;
            }
        }
        st[t] = true;
        res += dist[t];

        // 松弛
        for (int j = 0; j <= n; j++) {
            dist[j] = min(dist[j], w[t][j]);
        }
    }
    
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    
    // 读入点权
    // 设0号点为虚拟源点，连接所有节点i，边权为点权w[i]
    for (int i = 1; i <= n; i++) {
        cin >> w[0][i];
        w[i][0] = w[0][i];
    }

    // 读入边权
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> w[i][j];
        }
    }

    cout << prim() << endl;

    return 0;
}
