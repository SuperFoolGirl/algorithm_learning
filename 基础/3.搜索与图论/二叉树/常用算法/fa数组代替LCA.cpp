// fa数组的作用，就是记录每个结点的父结点，方便后续生成路径
// 重点是这个操作是在初始化时完成的，而不是在查询时动态生成路径
// 对于一切依赖于回溯的操作，用fa数组的迭代回溯会比递归更简单
// 用空间换时间

// 不只是二叉树，对于普通的树，也可以用fa数组记录路径

// 对于普通图，一个结点可能有多个父节点（前驱节点）。不能用fa在初始化时就完成记录
// 这时就需要在搜索过程中，动态记录每个结点的前驱节点，从而生成路径；而不是初始化时就记录好
// 例如用一个pre数组记录每个结点的前驱节点，类似的操作我也做过。自创的可能是正向/逆向，不过fa数组是逆向的
// BFS：边数最少字典序最小的最短路
// DFS：洛谷P2196 记忆化搜索
// dijkstra：松弛操作处记录前驱节点

#include <algorithm>
#include <cstring>
#include <iostream>


using namespace std;

typedef long long LL;

const int N = 1e5 + 10;

struct Node {
    int l = -1;
    int r = -1;
} tr[N];

int n;
int fa[N];
int node1, node2;
bool vis[N];

void add(int a, int b) {
    if (tr[a].l == -1) {
        tr[a].l = b;
    } else {
        tr[a].r = b;
    }
    fa[b] = a;
}

int findLCA() {
    // 记录从node1回溯到根节点的路径（根结点的父结点为0，这是默认初始化的）
    // 然后从node2开始回溯，遇到的第一个在路径上的节点即为LCA
    while (node1) {
        vis[node1] = true;
        node1 = fa[node1];
    }

    while (node2) {
        if (vis[node2]) {
            return node2;
        }
        node2 = fa[node2];
    }

    return -1;    // 理论上不会到这里
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        add(a, b);
    }

    cin >> node1 >> node2;    // 输入要查询的两个节点值。这里采用父子边列表，节点值即节点编号
    int lca = findLCA();

    return 0;
}
