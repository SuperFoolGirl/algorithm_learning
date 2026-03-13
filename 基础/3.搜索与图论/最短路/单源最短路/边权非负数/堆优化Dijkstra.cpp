// 回忆下朴素版本O(n^2)
/*
// 找最小的点
for(...) {
    for(...) {
    }
    // 更新最短路距离，由于所有的边都要访问到，因此这一步总的复杂度是O(m)
    for(...) {
    }
}
*/
// 进行堆优化的话，找最小点可以优化到O(1)
// 但更新距离，每一次操作为O(logn)，因此总的复杂度是O(mlogn)

// 两种堆：
// 1. 手写堆，堆中共n个元素
// 2. 优先队列，由于不支持修改任意元素，因此所有的边都需要入队，共m条边。复杂度O(mlogm)
// 从数学角度来看，二者几乎没有差别。直接用优先队列即可
// 在代码模板上，非常像bfs

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
int d[N];

void add(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;    // 存储边权
    ne[idx] = h[a];
    h[a] = idx++;
}

int dijkstra() {
    // 初始化距离
    memset(d, 0x3f, sizeof d);
    d[1] = 0;

    // PII的first值为距离，second值为点编号。不能交换，因为距离需要作为堆的比较依据
    // pair类型的比较函数是默认的，先比较第一字段，再比较第二字段
    // 注意，dist不可直接优化掉。因为d[]可能因为松弛操作而改变，所以需要直接push进去
    priority_queue<PII, vector<PII>, greater<PII>> heap;    // 小根堆
    heap.push({0, 1});                                      // 将起点加入堆

    while (!heap.empty()) {
        auto t = heap.top();
        heap.pop();

        int dist = t.first, node = t.second;

        // 出队只有一次，入队有若干次；因此终点判断在出队处
        if (node == n) {
            return dist;
        }

        // 出队判重
        // if (st[node]) {
        //     continue;
        // }
        // st[node] = true;
        // 一个点可能会入队多次，但只会出队一次；且保证出队的那唯一一次，dist一定是最小的
        // 如果被这段代码拦住，说明重复出队了；最优的一次已经出队过了，不允许再出队来执行下面的松弛操作了
        // 由于可能多次入队，堆里会有多个{dist,node}，但最优的数据已经写在d[node]中了
        // 因此，这里的条件可以改为 d[node] < dist，语义上不如st数组清晰，但省去了st数组
        if (dist > d[node]) {
            continue;
        }

        // 从t开始扩展与自己相邻的边
        for (int i = h[node]; i != -1; i = ne[i]) {    // 注意，h数组是用点编号来索引的
            int j = e[i];
            // 如果拓展出去的边，使得路径更短，就加入到堆中

            // 这里要说明一个松弛操作的特性：d[j]在可能的多次更新中，会越来越小的
            // 这一点在dijkstra的模拟中也很明显

            // 也就是说，只要发生了更新，新值一定比旧值小
            // 而堆中存留的关于节点j的所有副本中，值最小的那个会最先被弹出；后面其他副本弹出时会被continue剪枝
            // 所以，如果涉及路径的记录，直接在松弛操作处进行记录即可；会自动调整pre记录最短路径的

            // 松弛操作是“边权不同的最短路问题”能够多次入队的前提；对于边权相同问题，入队唯一，因此不需要松弛操作了
            
            if (d[j] > dist + w[i]) {    // 注意，w是以idx来索引的，而h记录的就是idx
                d[j] = dist + w[i];
                heap.push({d[j], j});    // 更新距离并将新节点加入堆
                // pre[j] = node;          // 可选：记录路径
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

    cout << dijkstra() << endl;

    return 0;
}
