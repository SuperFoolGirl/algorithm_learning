// 区间修改+区间查询
// 线段树信息维护：
// 1.区间和sum，需要考虑当前节点及其子结点上的所有懒标记；不考虑祖先(由pushdown解决)
// 2.懒标记add

#include <algorithm>
#include <cstring>
#include <iostream>


using namespace std;

typedef long long LL;

const int N = 100010;

struct Node {
    int l, r;
    LL sum, add;
} tr[N * 4];

int n, m;
int w[N];

void pushup(int u) {
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void pushdown(Node& u, Node& l, Node& r) {
    if (u.add) {
        l.add += u.add;
        r.add += u.add;
        l.sum += (LL)(l.r - l.l + 1) * u.add;
        r.sum += (LL)(r.r - r.l + 1) * u.add;
        u.add = 0;
    }
}

void pushdown(int u) {
    pushdown(tr[u], tr[u << 1], tr[u << 1 | 1]);
}

void build(int u, int l, int r) {
    tr[u] = {l, r};
    if (l == r) {
        tr[u].sum = w[l];
        return;
    }
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

// 区间修改，参数x变为参数l,r
void modify(int u, int l, int r, int v) {
    // 判断完全覆盖，若覆盖直接修改各属性
    if (tr[u].l >= l && tr[u].r <= r) {
        tr[u].sum += (LL)(tr[u].r - tr[u].l + 1) * v;
        tr[u].add += v;
        return;
    }
    // 此时需要分裂，需要先pushdown确保数据正确
    pushdown(u);
    // 下面的思路和基础query一样，两种情况版
    // 即使横跨mid，对于modify来说，也不需要考虑，因为不可能修改“新建结点”
    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid) {
        modify(u << 1, l, r, v);
    }
    if (r > mid) {
        modify(u << 1 | 1, l, r, v);
    }
    pushup(u);
}

// 无需返回Node，不需要返回懒标记
LL query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) {
        return tr[u].sum;
    }

    pushdown(u);
    // 本题也不需要考虑横跨mid的情况
    int mid = tr[u].l + tr[u].r >> 1;
    LL res = 0;
    if (l <= mid) {
        res = query(u << 1, l, r);
    }
    if (r > mid) {
        res += query(u << 1 | 1, l, r);
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    build(1, 1, n);

    char op[2];
    int l, r, d;
    while (m--) {
        cin >> op >> l >> r;
        if (*op == 'C') {
            cin >> d;
            modify(1, l, r, d);
        } else {
            cout << query(1, l, r) << '\n';
        }
    }

    return 0;
}
