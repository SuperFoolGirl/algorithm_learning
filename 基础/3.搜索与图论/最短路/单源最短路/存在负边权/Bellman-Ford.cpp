// 对于含有负权边构成的环，最短路问题可能无解
// 例如，每走一圈，总边权为负，那走无穷圈就会让路径变得无限短
// 这种问题在实际应用中不具备讨论价值
// 而Bellman-Ford算法可以检测到负权环

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 510, M = 10010;
int n, m, k;
// backup数组：备份
int dist[N], backup[N];

struct Edge {
    int a, b, w;
} edges[M];

int bellman_ford() {
    // 距离初始化为无穷大
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    // 遍历走i条边时，到达某点的最短距离
    // 下一轮循环，基于上一次，多走一条边，更新dist数组
    for (int i = 0; i < k; i++) {
        // 为了防止更新时的串联，先将当前状态备份
        // 比如在同一次循环中，刚更新了节点 a 的距离，马上用这个新距离去更新节点 b，这相当于在一次循环中走了两步
        memcpy(backup, dist, sizeof dist);

        // 松弛操作，基于上一轮更新的结果，探索下一步
        for (int j = 0; j < m; j++) {
            int a = edges[j].a, b = edges[j].b, w = edges[j].w;
            // a的最短距离 + 边权w = b的最短距离
            dist[b] = min(dist[b], backup[a] + w);
        }
    }

    if (dist[n] > 0x3f3f3f3f / 2) { // 超过k的路径
        return -1;
    }
    return dist[n];
}

int main() {
    // k:要求最短路长度不超过k
    cin >> n >> m >> k;

    // 读入边
    for (int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        edges[i] = {a, b, w};
    }

    int t = bellman_ford();

    if (t == -1) {
        cout << "impossible" << endl;
    } else {
        cout << t << endl;
    }

    return 0;
}
