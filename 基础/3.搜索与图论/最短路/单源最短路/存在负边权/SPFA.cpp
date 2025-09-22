// Bellman-Ford算法的优化版本，用bfs进行优化
// 优化对象是松弛操作。BF算法在松弛时，不一定每次都会更新，所以它比较傻，暴力遍历
// 松弛代码：dist[b] = min(dist[b], backup[a] + w)
// 如果a的dist不变小，那b的dist就不可能变小。也就是说a小了，其后继b才能小

// 大部分正权图题目也可以用SPFA来做，不需要Dijkstra
// 讲一下SPFA与Dijkstra的区别在哪
// SPFA用的是队列，而Dijkstra用的是优先队列。从根本上就不同。
// Dijkstra 是 "一次定终身"（节点出队后距离不变），SPFA 是 "反复修改"（节点可多次入队更新）

#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

typedef pair<int, int> PII;

const int N = 1e5 + 10, M = 2 * N;

int n, m;
int h[N], e[M], ne[M], idx;
int w[N];    // w[i]存储边i的权重
bool st[N];

// cnt数组用于处理负权环，如果没有可以不用
// 对于n个点的连通无环图（树），最多有n-1条边；如果cnt[x]>=n，说明走过的点超过了n，则必定有一个点走了两次，存在环
// 而在最短路的情况下还要走环，证明这个环一定是负权环
int d[N], cnt[N]; // cnt数组统计从起点到当前点最短路中边的数量，d数组存储当前点最短路长度

void add(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;    // 存储边权
    ne[idx] = h[a];
    h[a] = idx++;
}

int spfa() {
    memset(d, 0x3f, sizeof d);
    d[1] = 0;

    queue<int> q;
    q.push(1);
    // 所有在队列中的点，st数组都为true；反之则为false
    st[1] = true; // 防止队列中存储重复的点，但注意spfa算法中，节点可以多次入队

    while (!q.empty()) {
        int t = q.front();
        q.pop();

        st[t] = false; // 出队之后，标记为未在队列中，后续可以再次入队

        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            // 如果拓展出去的边，使得路径更短，就加入到队列中。可以将j视为中转点
            if (d[j] > d[t] + w[i]) {
                d[j] = d[t] + w[i];

                // 负权环相关判定
                cnt[j] = cnt[t] + 1; // 更新边的数量
                if (cnt[j] >= n) {
                    return -1; // 存在负权环
                }

                // 若当前边的起点距离被更新，则将其加入队列；这里正是对BF算法的优化
                if (!st[j]) {
                    q.push(j);
                    st[j] = true; // 标记入队
                }
            }
        }
    }

    if (d[n] == 0x3f3f3f3f) {
        return -1;
    } else {
        return d[n];
    }
}

int main() {
    cin >> n >> m;

    // 初始化表头，h[点]=边，所有点暂时无出边，即为-1
    memset(h, -1, sizeof h);

    while (m--) {
        int a, b, c;    // c为边权
        cin >> a >> b >> c;
        // 邻接表可以存储并处理重边，算法里会正确选择重边中最短的
        add(a, b, c);
    }

    // 算法里，把1号点作为起点了
    // 实际应用中，根据题目的不同需求，将模板变式即可
    cout << spfa() << endl;

    return 0;
}
