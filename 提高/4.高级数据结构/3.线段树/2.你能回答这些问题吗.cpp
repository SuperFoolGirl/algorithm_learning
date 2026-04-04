// 1.单点修改——pushup，不需要懒标记
// 2.查询区间内的最大连续子段和，需要存哪些信息？
// 区间端点永远不能丢
// tmax: 区间最大连续子段和
// 最大连续子段和：在[l,r]中，找到sum[a,b]的最大值，其中l<=a<=b<=r
// 和维护最值不一样，本题需要“连续”，不能直接从两个儿子处得到答案
// 对于情况2，我们要找到横跨左右子区间的最大子段和
// 应等价于左子区间的最大后缀+右子区间的最大前缀
// 因此还需要维护每个区间的最大前缀和lmax和最大后缀和rmax
// 注意，这里有个很大的误区：我们维护的直接子代lmax和rmax不一定恰好适用，但是可以递归！
// 线段树只要递归下去，就一定能找到恰好的区间！

// 除了上述属性，还需要维护什么呢？
// 我们要确保所有属性的完备性
// 对于已经给出的tmax, lmax, rmax
// 想一下，pushup中，lmax能正常更新吗？
// 其实是不能的：从结果来看，如果u的lmax横跨了mid，则说明，其lmax的构成来自于左儿子的全部+右儿子的lmax
// 不过，如果u的lmax没有横跨mid，则说明其lmax的构成来自于左儿子的lmax
// 因此，我们还需要维护一个属性sum，表示区间和
// 区间和本身是自然可求的，不需要新的依赖：u.sum = l.sum + r.sum
// 现在总结下所有属性的求法，验证其完备性。设当前节点为u，左儿子为l，右儿子为r
// 1.sum: u.sum = l.sum + r.sum
// 2.lmax: u.lmax = max(l.lmax, l.sum + r.lmax)
// 3.rmax: u.rmax = max(r.rmax, r.sum + l.rmax)
// 对于u结点的最大连续子段和tmax分为下列情况：没有横跨mid(全部来自l/r)、横跨了mid(来自l.rmax + r.lmax)
// 4.tmax: u.tmax = max(l.tmax, r.tmax, l.rmax + r.lmax)

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 500010;

struct Node {
    int l, r;
    int sum, lmax, rmax, tmax;
} tr[N * 4];

int n, m;
int w[N];

void pushup(Node& u, Node& l, Node& r) {
    u.sum = l.sum + r.sum;
    u.lmax = max(l.lmax, l.sum + r.lmax);
    u.rmax = max(r.rmax, r.sum + l.rmax);
    u.tmax = max(max(l.tmax, r.tmax), l.rmax + r.lmax);
}

// 重载一下，更好写
void pushup(int u) {
    pushup(tr[u], tr[u << 1], tr[u << 1 | 1]);
}

void build(int u, int l, int r) {
    tr[u].l = l, tr[u].r = r;  // 统一更新，不论是不是叶子都要更新区间端点
    if (l == r) {
        tr[u].sum = tr[u].lmax = tr[u].rmax = tr[u].tmax = w[l];
        return;
    }
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

void modify(int u, int x, int v) {
    if (tr[u].l == x && tr[u].r == x) {
        tr[u] = {x, x, v, v, v, v};
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

// 线段树的查询函数，返回一个Node结构体，包含了查询区间的所有属性
Node query(int u, int l, int r) {
    // 情况1
    if (tr[u].l >= l && tr[u].r <= r) {
        return tr[u];
    }

    int mid = tr[u].l + tr[u].r >> 1;

    // 此处，需要分3部分讨论，2部分不够
    // 对于横跨mid的情况，我们无法直接查询到，需要自己根据各属性去计算。逻辑在pushup中
    if (r <= mid) {
        // 此时，查询区间完全在左儿子中，直接递归查询左儿子
        return query(u << 1, l, r);
    } else if (l > mid) {
        // 此时，查询区间完全在右儿子中，直接递归查询右儿子
        return query(u << 1 | 1, l, r);
    } else {
        // 此时，查询区间横跨mid
        // 先找到左右两边的信息，注意查询范围和上述情况不同，边界为mid(+1)
        auto left = query(u << 1, l, mid);
        auto right = query(u << 1 | 1, mid + 1, r);
        // 然后根据左右两边的信息，计算出横跨mid的区间信息
        Node res;
        pushup(res, left, right);
        return res;
    }
} 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    build(1, 1, n);

    int k, x, y;
    while (m--) {
        cin >> k >> x >> y;
        if (k == 1) {
            if (x > y) {
                swap(x, y);
            }
            cout << query(1, x, y).tmax << '\n';
        } else {
            modify(1, x, y);
        }
    }

    return 0;
}
