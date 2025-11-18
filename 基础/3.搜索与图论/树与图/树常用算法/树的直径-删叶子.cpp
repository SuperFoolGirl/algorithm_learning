// 像拓扑排序一样，不断删除叶子节点，层层剥离
// 直到剩下的节点数小于等于2，这些节点就是树的直径的中心点
// 记录的层数，即为树的半径
// 无向图没有设置根，这里删除叶子的算法，最后留下来的节点才是“根”

// 无向图没有入度的概念，应称为度：连接到该节点的边的数量，也就是有向图中的入度+出度
// 叶子节点的度为1

#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

const int N = 1e5 + 10, M = 2 * N;
int h[N], e[M], ne[M], d[N], idx;    // 模拟邻接表存树

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

int diameter(int n) {
    queue<int> q;

    // 叶子节点入队
    for (int i = 1; i <= n; ++i) {
        if (d[i] == 1) {
            q.push(i);
        }
    }

    int layers = 0;    // 记录层数，即为树的半径
    int nodes = n;     // 记录剩余节点数

    while (nodes > 2) {
        layers++;
        // 处理本层叶子节点
        int sz = q.size();
        while (sz--) {
            int t = q.front();
            q.pop();
            nodes--;
            // 执行逻辑删除，访问过的节点度数置0
            d[t] = 0;

            // 遍历与t直接连接的所有结点(对应有向图中的父亲和儿子)
            // 但我们需要找到父亲即可，且父亲只有一个
            // 注意由于是无向图，这里有可能遍历到已经删除的节点
            // 所以将处理过的节点度数置为0，作为逻辑删除标记
            for (int i = h[t]; i != -1; i = ne[i]) {
                int j = e[i];
                // 如果j没有访问过，修正度数
                if (d[j] > 0) {
                    d[j]--;
                    // 如果j变成了叶子节点，加入队列
                    if (d[j] == 1) {
                        q.push(j);
                    }
                    // 父亲只有一个，这里找到的一定是唯一的那个父亲，可以直接跳出
                    break;
                }
            }
        }
    }

    // 直径记录的是经过的边数，而不是节点数
    // 若最终剩余节点为1，则直径为2*layers
    // 若最终剩余节点为2，则直径为2*layers+1
    return nodes == 1 ? layers * 2 : layers * 2 + 1;
}

int main() {
    int n;    // n为节点数
    cin >> n;
    memset(h, -1, sizeof h);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);    // 无向图，双向边
        d[a]++, d[b]++;          // 无向图，a和b的度都要加1
    }

    // 求直径并输出
    cout << diameter(n) << endl;

    return 0;
}
