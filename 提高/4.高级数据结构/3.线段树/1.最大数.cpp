// 初始序列为空，已知操作数为m，因此序列长度最多为m
// 先把m个坑准备好，全部初始化为0。用n记录已加入的数字个数
// 遇到加数指令时，视为修改n+1位置的数
// 因此，入队可以视为“单点修改”；再加上“求某区间的最值”，因此确定是线段树

// 相比树状数组求区间和，线段树是求区间某属性

// 根据题意，本题是动态查询，不可离线处理

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 200010;

struct Node {
    int l, r;
    int v;
} tr[N << 2];

int m, p;

void pushup(int u) {
    tr[u].v = max(tr[u << 1].v, tr[u << 1 | 1].v);
}

void build(int u, int l, int r) {
    tr[u].l = l, tr[u].r = r;
    if (l == r) {
        return;
    }
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
}

int query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) {
        return tr[u].v;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    int v = 0;
    if (l <= mid) {
        v = query(u << 1, l, r);
    }
    if (r > mid) {
        v = max(v, query(u << 1 | 1, l, r));
    }
    return v;
}

void modify(int u, int x, int v) {
    if (tr[u].l == x && tr[u].r == x) {
        tr[u].v = v;
        return;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    if (x <= mid) {
        modify(u << 1, x, v);
    } else {
        modify(u << 1 | 1, x, v);
    }
    pushup(u);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n = 0, last = 0;
    cin >> m >> p;
    build(1, 1, m);  // 根结点为1，区间为[1,m]

    char op[2];
    int x;
    while (m--) {
        cin >> op >> x;
        if (*op == 'Q') {
            // 查询后x个数，注意要从根开始搜，最大当前为n
            last = query(1, n - x + 1, n);
            cout << last << '\n';
        } else {
            // 修改第n+1个位置
            modify(1, ++n, (last + x) % p);
        }
    }

    return 0;
}
