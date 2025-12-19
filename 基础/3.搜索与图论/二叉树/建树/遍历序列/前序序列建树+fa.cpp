// idx从1开始对结点编号
// 因此全局共idx个结点，同时空结点可用0编号(非空从1开始)

// 根据遍历序列建树，节点编号和数据值是不等的
// fa数组记录的是基于结点编号的父子关系
// 如果直接给定数据值，要求寻找父亲，则需要进一步操作：
// 给定某点的数据值，如何快速找到该点，进而找到其父结点？
// 1. 遍历tr，找到tr[i].val == x的i，然后fa[i]即为父节点编号
// 2. 建树时，同时维护一个哈希表mp，key为数据值，value为结点编号
// 直接选择第二种

// 如果删除子树，只需要将父节点的对应子节点指针置0即可，即逻辑删除

#include <algorithm>
#include <cstring>
#include <iostream>
#include <unordered_map>

using namespace std;

const int N = 1e5 + 10;

struct Node {
    int val;
    int l;
    int r;
} tr[N];

int idx;
int fa[N];
unordered_map<int, int> mp;    // 数据值→结点编号

// p为当前递归结点的父结点
int buildTree(int p) {
    int val;
    cin >> val;
    if (val == 0) {
        return 0;
    }

    int curr = ++idx;
    mp[val] = curr;    // 记录数据值对应的结点编号
    fa[curr] = p;      // 构建父子关系

    tr[curr].val = val;
    tr[curr].l = buildTree(curr);
    tr[curr].r = buildTree(curr);

    return curr;
}

void preOrder(int u) {
    if (u == 0) {
        return;
    }
    cout << tr[u].val << " ";
    preOrder(tr[u].l);
    preOrder(tr[u].r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int root = buildTree(0);    // 根结点的父节点为0
    preOrder(root);
    cout << endl;

    // 测试：给定数据值，找到其父节点的数据值
    // 共m次查询
    int m;
    cin >> m;
    while (m--) {
        int x;
        cin >> x;
        int a = mp[x];
        int b = fa[a];  // 父节点编号
        if (b == 0) {
            // x是根节点，没有父节点
            cout << "0" << endl;
        } else {
            // 输出父节点的数据值
            cout << tr[b].val << endl;
        }
    }

    // 测试：删除子树，共k次
    // 注意，逻辑删除不容易处理删除已删除的部分，暂时不考虑
    // 如果涉及此类情况，建议用动态树结构
    int k;
    cin >> k;
    while (k--) {
        int x;
        cin >> x;
        int a = mp[x];
        int b = fa[a];

        if (b == 0) {
            // x是根节点，删除整棵树
            root = 0;
        } else {
            // 删除子树：将父节点对应的子节点指针置0
            if (tr[b].l == a) {
                tr[b].l = 0;
            } else {
                tr[b].r = 0;
            }
        }

        // 删除后输出前序遍历
        preOrder(root);
        cout << "\n";
    }

    return 0;
}
