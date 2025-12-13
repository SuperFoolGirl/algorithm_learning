// 结点从1开始，且1为根结点

#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

const int N = 1e5 + 10;

// 二叉树节点结构：值、左右子节点（-1表示无）
struct Node {
    int l = -1;
    int r = -1;
} tr[N];

int n;        // 节点总数（1~n）
int fa[N];    // 可选：记录父节点（树形DP/路径题需要）

// 添加边：a是父节点，b是子节点，自动填充左/右子节点（先左后右）
void add(int a, int b) {
    if (tr[a].l == -1) {    // 左子女为空，填左
        tr[a].l = b;
    } else {                // 左子女已存在，填右（二叉树最多2个子节点）
        tr[a].r = b;
    }
    fa[b] = a;              // 可选
}

// 前序遍历（根→左→右）
void preOrder(int u) {
    if (u == -1) {
        return;
    }
    cout << u << " ";
    preOrder(tr[u].l);
    preOrder(tr[u].r);
}

// 层序遍历（广度优先）
void levelOrder(int root) {
    if (root == -1) {
        return;
    }
    queue<int> q;
    q.push(root);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";
        if (tr[u].l != -1) {
            q.push(tr[u].l);
        }
        if (tr[u].r != -1) {
            q.push(tr[u].r);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 输入节点总数
    cin >> n;

    memset(fa, -1, sizeof fa);  // 可选

    // 输入n-1条边（任意顺序，a是父，b是子）
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
    }

    // 根节点固定为1号，执行遍历验证
    cout << "前序遍历（根=1）：";
    preOrder(1);
    cout << endl;

    cout << "层序遍历（根=1）：";
    levelOrder(1);
    cout << endl;

    return 0;
}
