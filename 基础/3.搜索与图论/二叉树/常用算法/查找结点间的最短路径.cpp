// 建树时使用fa数组以便后续生成路径；
// PTA中用递归回溯时自然记录路径，有些复杂；另外还要用lca算法
// 而fa数组可以很快地找到lca

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

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
vector<int> path1, path2;

void add(int a, int b) {
    if (tr[a].l == -1) {
        tr[a].l = b;
    } else {
        tr[a].r = b;
    }
    fa[b] = a;
}

int findLCA(int val1, int val2) {
    while (val1) {
        vis[val1] = true;
        val1 = fa[val1];
    }

    while (val2) {
        if (vis[val2]) {
            return val2;
        }
        val2 = fa[val2];
    }

    return -1;    // 理论上不会到这里
}

void findPath() {
    int val1 = node1, val2 = node2;
    int lca = findLCA(val1, val2);

    // 从node1回溯到lca，记录路径
    while (val1 != lca) {
        path1.push_back(val1);
        val1 = fa[val1];
    }
    // 加入lca节点
    path1.push_back(lca);

    // 从node2回溯到lca，记录路径
    while (val2 != lca) {
        path2.push_back(val2);
        val2 = fa[val2];
    }
    // 反转path2，使其从lca到node2
    reverse(path2.begin(), path2.end());

    // 合并两条路径
    for (int v : path2) {
        path1.push_back(v);
    }
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

    cin >> node1 >> node2;
    findPath();
    for (int v : path1) {
        cout << v << " ";
    }

    return 0;
}
