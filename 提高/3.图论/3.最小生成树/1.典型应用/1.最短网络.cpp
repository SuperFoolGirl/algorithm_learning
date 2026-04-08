// 纯mst，给邻接矩阵，那直接prim

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110;

int n;
int w[N][N];
int dist[N];  // 存储外界点到mst的距离
bool st[N];  // st[i]表示i点是否在mst中

int prim() {
    int res = 0;
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;  // 必须得设置一个0作为起点，否则无法执行算法；从1号点开始构建mst

    // 每次选出一个点加入mst，n次
    for (int i = 0; i < n; i++) {
        int t = -1;
        // 枚举所有点，打擂台找出本轮加入mst的点t
        for (int j = 1; j <= n; j++) {
            if (!st[j] && (t == -1 || dist[t] > dist[j])) {
                t = j;
            }
        }

        res += dist[t];
        st[t] = true;
        // t点加入mst了，松弛操作
        // 注意松弛方程，j到mst的最短距离，一定是只通过w一条边就能确定的
        // 本身prim算法求mst时，树外点也是直接一条边连到树内某点的
        // 别和最短路搞混了
        for (int j = 1; j <= n; j++) {
            dist[j] = min(dist[j], w[t][j]);
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> w[i][j];
        }
    }

    cout << prim() << endl;

    return 0;
}
