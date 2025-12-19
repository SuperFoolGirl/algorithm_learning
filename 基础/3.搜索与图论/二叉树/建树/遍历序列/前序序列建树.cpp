// 用结构体来存储结点

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 1e5 + 10;

// 结构体数组
struct Node {
    int val;
    int l;
    int r;
} tr[N];

int idx;    // 记录用到了哪个结点，而不是哪条边；不可省略

// 递归构建二叉树，返回根节点的索引
int buildTree() {
    int val;
    cin >> val;        // 读取当前节点值（前序顺序）
    if (val == 0) {    // 0表示空节点，返回0
        // 初始化时，l/r均为0，无需重复赋值
        return 0;
    }

    // idx是全局变量，不可用它做返回值。这里必须缓存
    int curr = ++idx;

    tr[curr].val = val;    // 创建结点，自己开辟一个新的索引
    // 动态树中，l/r作为参数传入递归函数；静态树中作为左值
    tr[curr].l = buildTree();    // 递归构建左子树，赋值给u的左子节点
    tr[curr].r = buildTree();    // 递归构建右子树，赋值给u的右子节点

    // 必须返回缓存值，否则idx作为全局变量，在回到本层递归时，idx与curr不等
    return curr;               // 返回当前节点的索引
}

// 输入：当前节点索引；输出：前序遍历结果
void preOrder(int u) {
    if (u == 0) {    // 空节点
        return;
    }
    cout << tr[u].val << " ";    // 访问根节点
    preOrder(tr[u].l);           // 遍历左子树
    preOrder(tr[u].r);           // 遍历右子树
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int root = buildTree();  // 其实就是tr[1]
    preOrder(root);

    return 0;
}
