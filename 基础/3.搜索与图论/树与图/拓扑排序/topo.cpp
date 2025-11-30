// 仅针对有向图。无向图无拓扑序列
// 如果图中存在环，则无法进行拓扑排序
// 有向无环图一定存在拓扑序列，因此有向无环图也成为拓扑图

// 对有向图的节点进行排序，使得总能够满足每条边的起点在终点之前
// 例如，给定图
// 1 -> 2
// 1 -> 3
// 2 -> 4
// 3 -> 4
// 4 -> 5
// 可能的拓扑排序有：1 2 3 4 5 或 1 3 2 4 5
// 以1 2 3 4 5为例，对于2来说，指向后面的点3，4，5，图中一定存在这样的路
// 也就是说，拓扑排序中，靠前的点指向靠后的点，在原图中是一定存在路的

// 边的增减用入度数组d来维护

#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int N = 1e5 + 10, M = 2 * N;
int n, m;
int h[N], e[M], ne[M], idx;
int d[N], q[N];    // d为入度数组
vector<int> res;

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

// 如果是有向无环图，则返回true；否则返回false
// 从图中找到入度为 0 的节点，然后将其从图中移除，并更新其邻接点的入度。重复此过程，直到所有节点都被移除。
bool topo_sort() {
    // 把入度为0的点放到队列里
    // 注意，当没有起点入队时，tt要改为-1，来使得q[++tt]的一致性成立
    // 有起点入队，直接令tt=0，然后赋值q[0]即可。这种场景用在bfs比较多，不过建议直接统一初始化为-1来统一代码逻辑
    queue<int > q;
    for (int i = 1; i <= n; i++) {
        if (!d[i]) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int t = q.front();
        q.pop();

        // 将t加入拓扑序列，在取出队列元素后加入，可以保证不重不漏
        res.push_back(t);

        // 找到所有出边
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            // 现在要拿走t这条边，所以所有t的出边对应的点，入度-1
            d[j]--;
            // 如果入度改变后，出现了新的入度为0的点，那就加入队列
            if (d[j] == 0) {
                q.push(j);    // j是e数组的元素。e[idx]存储的是 索引为idx的这条边 所指向的目标节点，即出边指向的点。队列里放的是点
            }
        }
    }

    return res.size() == n;
}

int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
        d[b]++;    // b的入度加1
    }

    if (topo_sort()) {
        // 打印拓扑排序的n个点
        for (int i = 0; i < n; i++) {
            cout << res[i] << " ";
        }
    } else {
        puts("-1");
    }

    return 0;
}
