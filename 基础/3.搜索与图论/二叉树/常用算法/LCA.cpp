#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10;

struct Node {
    int l = -1;
    int r = -1;
} tr[N];

int n;
int val1, val2;

void add(int a, int b) {
    if (tr[a].l == -1) {
        tr[a].l = b;
    } else {
        tr[a].r = b;
    }
}

int findLCA(int t) {
    if (t == -1) {
        return -1;
    }
    // 递归下去后，找到目标结点了，返回到LCA结点调用处
    if (t == val1 || t == val2) {
        return t;
    }

    int left = findLCA(tr[t].l);
    int right = findLCA(tr[t].r);

    // 如果左右子树都找到目标结点了，说明当前结点就是LCA
    if (left != -1 && right != -1) {
        return t;
    }

    // 说明本层t不是LCA，LCA在t的左子树或右子树，或者都没找到
    return left != -1 ? left : right;
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

    cin >> val1 >> val2;  // 输入要查询的两个节点值。这里采用父子边列表，节点值即节点编号
    int lca = findLCA(1);  // 寻找val1和val2对应节点的最近公共祖先

    return 0;
}
