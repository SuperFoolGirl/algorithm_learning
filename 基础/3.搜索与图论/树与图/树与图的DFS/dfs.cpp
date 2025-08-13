// 对于树来说，树的深度优先搜索，其实就是前/中/后序遍历

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10, M = N * 2;
int n, m; // n为点数，m为边数
int h[N], e[M], ne[M], idx;
bool st[N]; // 记录已经搜过的点

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

void dfs(int x) {
    st[x] = true;

    // 根据打印语句命令的位置不同，决定遍历方式
    // 该模板无法完成中序遍历，因此这里只给出前序和后序

    // 前序遍历：还没开始遍历自己的孩子，就先输出根节点
    // cout << x << ' ';

    // 从每个点的头结点开始，去遍历它的孩子们
    // 但还没等开始遍历，就先递归下去了，直到尾结点
    // 等到递归回来时，再依次遍历当前点的孩子，然后这些孩子再递归下去...
    for (int i = h[x]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!st[j]) {
            dfs(j);
        }
    }

    // 后序遍历：等到所有孩子都遍历完了，才输出根节点
    // cout << x << ' ';
}

int main() {
    memset(h, -1, sizeof h);

    // 构建图
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
    }

    dfs(1);
    return 0;
}
