#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 1e5 + 10;

struct Node {
    int val;
    int l = -1;
    int r = -1;
} tr[N];

int idx;
int fa[N];

int buildTree(int p) {
    int val;
    cin >> val;
    if (val == 0) {
        cout << "0 ";
        return -1;
    }

    int curr = ++idx;
    tr[curr].val = val;
    fa[curr] = p;
    tr[curr].l = buildTree(idx);
    tr[curr].r = buildTree(idx);

    return idx;
}

void preOrder(int u) {
    if (u == -1) {
        cout << "0 ";
        return;
    }
    cout << tr[u].val << " ";
    preOrder(tr[u].l);
    preOrder(tr[u].r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    memset(fa, -1, sizeof fa);
    int root = buildTree(-1);    // 传入父结点索引
    preOrder(root);

    return 0;
}
