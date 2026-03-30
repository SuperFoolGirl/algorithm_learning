// 看到不等式链，意识到是简化版差分约束
// 如果差分约束保证都是非负权边，还可以SCC，效率更高
// 不过DAG确实是最简单的偏序关系

// 本题中，所有边权都是正1，那很简单了
// 本身作为DAG，直接省去了tarjan缩点步骤，直接在原图上递推求最长路即可

// 总结差分约束问题
// 1.边权无限制：spfa
// 2.边权非负：tarjan缩点+DAG求最长路
// 3.边权>0：DAG求最长路

// 代码技巧：
// 本题可以设置虚拟源点连向每条边，边权为100，以满足最少100的条件
// 当然，可以预想一下：虚拟源点第一步扩散后，其他点的dist就会更新为100
// 这里的思路在之前也有讲过，模拟虚拟源点的扩散来体会其用途
// 因此，可以直接将所有dist初始化为100，省去这个虚拟源点

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 10010, M = 20010;

int n, m;
int h[N], e[M], ne[M], idx;
int q[N];
int d[N];
int dist[N];

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

bool toposort() {
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

    // 判断环
    return tt == n - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    memset(h, -1, sizeof h);

    while (m--) {
        int a, b;
        cin >> a >> b;
        // 所有边权都为1，因此不用存了，直接在三角不等式里体现即可
        // 别忘了差分约束的加边方向，不等号右边指向左边
        add(b, a);
        d[a]++;
    }

    // 拿到拓扑序后才能跑DP。拓扑序在q中
    if (!toposort()) {
        cout << "Poor Xed" << endl;
    } else {
        for (int i = 1; i <= n; i++) {
            dist[i] = 100;  // 模拟虚拟源点扩散的结果，满足最少100的条件
        }

        for (int u = 0; u < n; u++) {
            int t = q[u];  // t为按拓扑排序取出的点
            for (int i = h[t]; ~i; i = ne[i]) {
                int j = e[i];
                dist[j] = max(dist[j], dist[t] + 1);
            }
        }

        int res = 0;
        for (int i = 1; i <= n; i++) {
            res += dist[i];
        }
        cout << res << endl;
    }

    return 0;
}
