// 操作1：区间[L,R]每个数加d
// 操作2：查询区间[L,R]的最大公约数

// 线段树信息(区间端点略)：
// 最大公约数
// 设区间[L,R]的gcd为c，倘若区间整体加d，那么无法直接更新gcd
// 同时修改一个区间非常难做，但令其都递归到叶子，回溯时pushup，一番周折后自然完成就可以了
// 这里先给出一个gcd等式：gcd(x,y,z) = gcd(x,y-x,z-y)
// 证明等式的思路一般是两边互相大于等于，类似集合相等的证法。这里略
// 而上述等式的形式，与差分是很像的
// 因此，让线段树维护差分值
// 对于区间[L,R]的结点，其最大公约数应为gcd(a[L], gcd(b[L+1]~b[R]))，其中b[i]=a[i]-a[i-1]

// 由于线段树里维护的是差分值，而我们又需要去获取原数组的值
// 也就是说，输入的是a[i]，但我们存的是b[i]
// 因此，我们还需要维护一个sum前缀和，来得到原数组

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 500010;

struct Node {
    int l, r;
    LL sum, d;
} tr[N << 2];

int n, m;
LL w[N];

LL gcd(LL a, LL b) {
    return b ? gcd(b, a % b) : a;
}

void pushup(Node& u, Node& l, Node& r) {
    u.sum = l.sum + r.sum;
    u.d = gcd(l.d, r.d);  // 区间的gcd等于左右子区间的gcd
}

void pushup(int u) {
    pushup(tr[u], tr[u << 1], tr[u << 1 | 1]);
}

void build(int u, int l, int r) {
    tr[u].l = l, tr[u].r = r;
    if (l == r) {
        LL b = w[l] - w[l - 1];  // 差分值
        tr[u].sum = tr[u].d = b;  // 叶子的sum也应当是差分值，sum是差分值的和
        return;
    }
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

Node query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) {
        return tr[u];
    }
    int mid = tr[u].l + tr[u].r >> 1;
    // 本题横跨左右两边的查询也需要特别处理，不能同时处理
    if (r <= mid) {
        return query(u << 1, l, r);
    } else if (l > mid) {
        return query(u << 1 | 1, l, r);
    } else {
        // 还是先拿到结果，然后再更新
        // 其实这里挺好理解的，锁定住具体横跨的范围，然后用这个范围来更新其“父亲”res就好了
        // 可以这么理解：u的子区间分别为[u.l,mid]和[mid+1,u.r]
        // 但我们需要的区间[l,r]包含在[u.l,u.r]中，横跨了mid，因此我们要截取出[l,mid]和[mid+1,r]
        // 由于我们凭空造出了两个结点[l,mid]和[mid+1,r]，则它们的“父亲”就是res，直接pushup更新父亲就好
        auto left = query(u << 1, l, mid);
        auto right = query(u << 1 | 1, mid + 1, r);
        Node res;
        pushup(res, left, right);
        return res;
    }
}

void modify(int u, int x, LL v) {
    if (tr[u].l == x && tr[u].r == x) {
        LL b = tr[u].sum + v;  // 修改差分值
        tr[u] = {x, x, b, b};  // sum和d都要修改
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

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    build(1, 1, n);

    int l, r;
    LL d;
    char op[2];
    while (m--) {
        cin >> op >> l >> r;
        if (*op == 'Q') {
            // 查询区间[L,R]的最大公约数，用上面讲的公式
            auto left = query(1, 1, l), right = query(1, l + 1, r);
            cout << abs(gcd(left.sum, right.d)) << '\n';
        } else {
            cin >> d;
            modify(1, l, d);
            if (r + 1 <= n) {
                // 注意特判越界
                modify(1, r + 1, -d);
            }
        }
    }

    return 0;
}
