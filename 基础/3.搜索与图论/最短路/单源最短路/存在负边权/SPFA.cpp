// 时间复杂度：一般O(m)，最坏O(nm)
// 一般情况下比堆优化Dijistra的O(mlogn)更好
// SPFA本身作为Bellman-Ford算法优化，基本上完全压制了BF的出场空间

// 算法操作：
// 1.建立队列，放入起点
// 2.建立dist记录起始点到所有点的最短距离，需要初始化为无穷大
// 3.扩展+松弛，用当前点更新到所有点的最短路；如果更新成功，新点入队。直至队列为空

// 大部分正权图题目也可以用SPFA来做，不需要Dijkstra
// 讲一下SPFA与Dijkstra的区别在哪 
// SPFA用的是队列，而Dijkstra用的是优先队列
// 其实理解了Dijkstra，就能够理解SPFA了
// Dijkstra基于贪心思想，用优先队列保证每个节点第一次出队时，一定就是最短路
// 而SPFA就更加摆烂一些，只要遇到更好的结果就入队，并不特意维护队列的秩序；因此，入队和出队都没有限制
// 如此循环直到队列为空，意味着再也没有更好的结果了
// 因此，从直觉上来说，SPFA是更朴素、更像BFS的算法——知错就改，直到改无可改

// 而为什么队列中不能存储重复的点呢？
// 我们看看队列中的元素是什么——{点}，而不是{点,距离}
// 这就是根本区别所在
// 当松弛A时，A->B可更新，但此时B已经在队列中了；若再入队，则队列中有两个{B}，而不是{B,距离1}和{B,距离2}
// 在入队前，dist[B]已经被修改了，这就够了；当B出队时，会根据修改后的dist[B]来松弛
// 而如果队列中没有B，那必须把它请回来，让他用更加新的数据来重新松弛他的邻居；随后这些邻居们可能又要入队...

// 下面讲一下更本质的内容：
// 最短路问题本质上是在解一组三角不等式组：d[u]<=d[v]+w(u,v)
// SPFA的执行过程，实际上就是不断地挑出那些违背了不等式的边，强制让它们满足等式。直到所有边都满足了，算法自然停止

#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

typedef pair<int, int> PII;

const int N = 1e5 + 10, M = 2 * N;

int n, m;
int h[N], e[M], ne[M], idx;
int w[M];    // w[i]存储边i的权重
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

                // 若当前边的起点距离被更新，则将其加入队列
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
