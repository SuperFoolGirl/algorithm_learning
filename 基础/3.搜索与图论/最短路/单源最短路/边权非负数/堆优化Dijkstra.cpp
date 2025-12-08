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
bool st[N];

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
    // 注意，dist不可直接优化掉。因为d[]可能因为松弛操作而改变，所以需要直接push进去
    priority_queue<PII, vector<PII>, greater<PII>> heap;    // 小根堆
    heap.push({0, 1});                                      // 将起点加入堆

    while (!heap.empty()) {
        auto t = heap.top();
        heap.pop();

        int dist = t.first, node = t.second;

        // 剪枝
        if (node == n) {
            return dist;
        }

        // dijkstra是基于贪心思想的，一旦一个点被加入最短路集合，就已经确定最短了，不能再修改了
        // 但是，不能放到下面for循环里，像很多BFS题目那样，只要遇到就标记
        // 因为，node被push进堆后，下一次不一定立刻就会pop出来；这个node可能还要被多次松弛操作，更新距离并重新push进堆
        // 这个多次松弛是关键，某个点可能是被多次松弛后才最终确定最短路的，这也是此前一直忽略的点
        // 此时堆里会有多个node，但距离各不相同。显然，距离小的会被先pop出来，然后标记后，其他node就不能再更新了
        
        // 因此，这里的条件可以改为 d[node] < dist，语义上不如st数组清晰，但与松弛条件进行统一了
        // 这个点要好好体会，不可一知半解
        if (st[node]) {
            continue;
        }
        st[node] = true;    // 标记当前节点已经在最短路中

        // 从t开始扩展与自己相邻的边
        for (int i = h[node]; i != -1; i = ne[i]) {    // 注意，h数组是用点编号来索引的
            int j = e[i];
            // 如果拓展出去的边，使得路径更短，就加入到堆中
            if (d[j] > dist + w[i]) {    // 注意，w是以idx来索引的，而h记录的就是idx
                d[j] = dist + w[i];
                heap.push({d[j], j});    // 更新距离并将新节点加入堆
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
