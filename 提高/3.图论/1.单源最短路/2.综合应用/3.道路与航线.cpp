// 与拓扑排序结合
// 拓扑序的充要条件：有向无环图

// 整理题目条件
// 道路双向，边权非负
// 航线单向，边权可负
// 将图中的若干点视为一个集合
// 集合内只有道路，不会有航线
// 各集合之间由航向连接，且满足拓扑序(无环)

// 本题spfa会被卡成O(nm)，因此用不了
// 那如何处理负权边呢？
// 下面给出两个原则：
// 1.如果边权非负，那么可以用dijkstra求最短路
// 2.如果是拓扑图，那么不管边权正负，均可按拓扑序扫描，时间复杂度为线性，直接求出最短路

// 因此，集合内道路用dijkstra；航线满足拓扑序，因此可以按拓扑序扫描求最短路
// 先输入道路，然后跑flood fill/并查集求出所有连通块，再输入航线
// 外部跑拓扑，跑到哪个集合，集合内部跑dijkstra
// 本题的航线有重边，不过不影响拓扑序

// 块内是无向边，航线是有向边；因此块内各点互相可达，但起点s在跨越航路去访问其他点的话，则不一定走的到

// 代码细节
// 1.输入道路，找连通块，计算id[]存储每个点属于哪个连通块，vector<int> block存储每个连通块里有哪些点
// 2.输入航线，统计出每个连通块的入度
// 3.按拓扑序处理每个连通块
// 4.对于每次出队的连通块，将其中所有点入堆，执行dijkstra

#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>


#define x first
#define y second

    using namespace std;

typedef pair<int, int> PII;

const int N = 25010, M = 150010, INF = 0x3f3f3f3f;

int n, mr, mp, S;    // mr: 道路数量，mp: 航线数量，S：起点
int h[N], e[M], ne[M], w[M], idx;
int id[N];
vector<int> block[N];
int dist[N];
int din[N];      // 入度
bool st[N];
int bcnt;        // 连通块编号
queue<int> q;    // 用于toposort

void add(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

void dfs(int u, int bid) {
    id[u] = bid;
    block[bid].push_back(u);

    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (id[j]) {
            continue;
        }
        dfs(j, bid);
    }
}

// 把bid中所有点入堆
// 根据拓扑序，当前bid的入度已经为0，所有指向bid的入边已经处理过了
// 因此，bid中必然有点的dist已经更新过，不再是INF了
// 这样，将所有点入堆，就会找出dist最小的点，即“当前连通块的起点”
// 这样并不会对dijkstra算法本身产生影响：st会保证每个点只出队一次，而全部入堆时，未更新过的点的distance字段都是INF；又因为块内联通，不存在不可达，因此它们一定都会堆积到堆后面，然后被st拒之门外
// 因此，对于普通的dijkstra问题，也可以一股脑全部入堆而不只起点；不过这样毫无意义就是了

// 当然，有一种情况除外：S不可达的连通块A。由于航线是有向图，因此两块间不一定可达
// 设想第一轮拓扑排序，入度为0的块A跑dijkstra；如果S不在其中，那么所有点的dist都是INF，这种情况下，无法做松弛操作，所有由正权边连接的点，都将还是INF
// 宏观来看，因为它是S不可达的块A，因此它内部的最短路就无所谓了，算不算都一样

// 这里需要提一句，航路有负权边
// 对于A中的点ver->B中的点j的航路，假设它是负权边，根据代码，它会在A的点进行dijksra时执行ver->j的松弛
// 在这种情况下，j不同于A中的点们，会被更新:
// dist[j]>distance+w[i]，即INF>INF+负数，因此dist[j]会被更新为一个略小于INF的点——但实际上，j也可能是不可达的——如果只能通过A到达B，那么B中的点对于S来说也不可达——除非S能通过其他点到达B块
// 因此，在有负边权的情况下，dist[i]==INF不能作为不可达的判断条件，它只是一个子集；dist[i]略小于INF的点，也可能是不可达的；因此，最后输出时，只要dist[i]大于某个大数字，就认为它不可达
void dijkstra(int bid) {
    priority_queue<PII, vector<PII>, greater<PII>> heap;

    for (auto ver : block[bid]) {
        heap.push({dist[ver], ver});
    }

    while (heap.size()) {
        auto t = heap.top();
        heap.pop();

        int ver = t.y, distance = t.x;
        if (st[ver]) {
            continue;
        }
        st[ver] = true;

        for (int i = h[ver]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] > distance + w[i]) {
                // 注意这一行：不管j是连通块内的点，还是连通块外的点，都要更新距离
                dist[j] = distance + w[i];

                // 扩展的边指向连通块内的点，而不是块与块间的航线
                if (id[j] == id[ver]) {
                    heap.push({dist[j], j});
                }
            }

            // 如果是航线，且指向的连通块入度减到0了
            if (id[j] != id[ver] && --din[id[j]] == 0) {
                q.push(id[j]);
            }
        }
    }
}

void toposort() {
    // 我们的任务，是求S到其他所有点的最短路，这是起点
    memset(dist, 0x3f, sizeof dist);
    dist[S] = 0;

    // 先将入度为0的连通块入队
    for (int i = 1; i <= bcnt; i++) {
        if (!din[i]) {
            q.push(i);
        }
    }

    while (q.size()) {
        int t = q.front();
        q.pop();

        dijkstra(t);  // 内部会处理入度自减、新入队
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> mr >> mp >> S;
    memset(h, -1, sizeof h);

    // 输入道路，找连通块
    while (mr--) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);
    }

    // 暴搜连通块
    for (int i = 1; i <= n; i++) {
        if (!id[i]) {
            dfs(i, ++bcnt);
        }
    }

    // 输入航线，统计入度
    // 两个连通块之间可能有多条边，不过无所谓，不影响拓扑序的排列，只要遍历到这些边就会修改入度
    while (mp--) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);    // 有向边
        din[id[b]]++;
    }

    toposort();

    // 如果存在负权边，不可达点的距离不一定只有INF，还有别的(在dijkstra处详细讲了)
    // 因此，只要是一个大数字，就认为是不可达点，这里取INF/2
    for (int i = 1; i <= n; i++) {
        if (dist[i] > INF / 2) {
            cout << "NO PATH" << endl;
        } else {
            cout << dist[i] << endl;
        }
    }

    return 0;
}
