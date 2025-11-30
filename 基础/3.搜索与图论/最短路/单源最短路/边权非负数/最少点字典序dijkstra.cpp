// 以dijkstra为例的BFS变种题目，可以进行以下总结
// 1. 题目的要求是松弛的指标，经典的dijkstra只涉及距离这一项，也就是经典题目的要求
// 2. 队列结构体存储松弛操作的指标
// 3. 自己需要额外维护数组，来记录松弛操作的各个指标
// 4. 松弛操作时，依次根据各个指标进行松弛，并更新所有指标的值(来到次级字段，则前面的字段相等，因此就不用修改)
// 5. 优先队列的排序函数也需要根据这些指标进行修改
// 6. 重复入队判断，实质上是根据松弛指标来的。如经典dijkstra中，vis数组可以换成类似 t.dist > d[t.id] 的判断
//    如果t.dist > d[u]，则说明t是一个过时的、较长的路径，直接将其剪枝
//    如果t.dist =d[u]，则说明这是第一次或携带最短路径出队，进行松弛扩展。

// 根据上述总结，分析本题
// 经典dijkstra的松弛操作，只涉及距离
// 本题相当于增加了松弛操作的指标，分成了三个字段
// 1.距离  2.路径长度  3.路径字典序
// ① 而如果想要丰富松弛操作的指标，就需要扩充队列的节点结构体
// ② 除了松弛操作要丰富，优先队列的排序函数也需要根据这些字段进行修改
// ③ 还需要配套的数组，如d用来记录dist，pre用于回溯构建路径，len用于记录路径长度
// ④ 修改判断重复入队的条件
// 这里要补充一下，通过pre来回溯构建路径是图论常用的技巧，使用数据结构来存储路径的开销较大，且不易维护

// 另外，字典序逻辑需要从头判断，无法像dist和len一样直接维护；pre在松弛时更新，但字典序指标确实需要找回去
// 因此，剪枝和队列都不涉及字典序；在字典序的松弛时，也无需执行入队操作，只需更新pre即可

#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int N = 2e4 + 10, M = N;

// id是必须维护的基础字段，其他字段由松弛操作决定
struct node {
    int id;
    int dist;
    int len;
};

// 为松弛指标定义优先级
struct Comparator {
    bool operator()(const node& a, const node& b) {
        // 字段优先级：距离 > 路径长度 > 字典序
        if (a.dist != b.dist) {
            return a.dist > b.dist;
        } else {
            return a.len > b.len;
        }
    }
};

int n, m;
int h[N], e[M], ne[M], idx;
int w[M];
int d[N], pre[N], len[N];

void add(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

void dijkstra() {
    // 初始化各数组信息
    // d, len涉及松弛操作，需要初始化为松弛指标的相反最值
    memset(d, 0x3f, sizeof d);
    memset(pre, -1, sizeof pre);
    memset(len, 0x3f, sizeof len);

    d[0] = 0;    // 千万别忘了。。

    priority_queue<node, vector<node>, Comparator> heap;
    heap.push({0, 0, 1});

    while (!heap.empty()) {
        auto t = heap.top();
        heap.pop();

        int dist = t.dist, id = t.id, length = t.len;

        // 重复入队判断
        if (dist > d[id] || (dist == d[id] && length > len[id])) {
            continue;
        }

        // 从t开始扩展与自己相邻的边
        for (int i = h[id]; i != -1; i = ne[i]) {
            int j = e[i];
            int new_dist = dist + w[i];
            int new_len = length + 1;
            // 根据字段优先级，依次进行松弛操作
            if (d[j] > new_dist) {
                // 1. 距离
                d[j] = new_dist;
                pre[j] = id;
                len[j] = new_len;
                heap.push({j, d[j], len[j]});
            } else if (d[j] == new_dist && len[j] > new_len) {
                // 2. 路径长度
                pre[j] = id;
                len[j] = new_len;
                heap.push({j, d[j], len[j]});
            } else if (d[j] == new_dist && len[j] == new_len) {
                // 3. 字典序，需要回溯逐位构建
                // 回溯构建当前路径
                vector<int> curr_path;
                int x = id;
                while (x != -1) {
                    curr_path.push_back(x);
                    x = pre[x];
                }
                reverse(curr_path.begin(), curr_path.end());
                // 回溯构建已有路径
                vector<int> exist_path;
                x = j;
                while (x != -1) {
                    exist_path.push_back(x);
                    x = pre[x];
                }
                reverse(exist_path.begin(), exist_path.end());
                // 比较字典序
                if (curr_path < exist_path) {
                    pre[j] = id;
                    // 无需入队，因为字典序相关字段根本不在队列结构体中，入队的是完全一样的结点
                }
            }
        }
    }
}

int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);

    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
    }

    dijkstra();

    for (int i = 1; i < n; ++i) {
        // 不可达则不输出
        if (d[i] == 0x3f3f3f3f) {
            continue;
        }

        // 回溯构造路径
        vector<int> path;
        int x = i;
        while (x != -1) {
            path.push_back(x);
            x = pre[x];
        }
        reverse(path.begin(), path.end());

        bool flag = true;
        for (int node : path) {
            if (!flag) {
                cout << "->";
            }
            cout << node;
            flag = false;
        }
        cout << "\n";
    }

    return 0;
}
