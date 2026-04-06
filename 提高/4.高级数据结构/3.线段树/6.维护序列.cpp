// 操作：区间乘、区间加、区间求和
// 只要涉及区间修改，那就是懒标记
// 线段树信息维护：
// l,r,sum,add懒标记，这四个就不多说了
// 只需要加一个mul懒标记。关键是如何更新这个懒标记对sum带来的影响
// 这里给出一个技巧：将加和乘看成一个操作，每次对sum执行sum*mul+add操作
// 如果操作是加：mul=1，add=c
// 如果操作是乘：mul=c，add=0
// 下面来看一下懒标记叠加能否正确处理：
// 假设已经有打上了懒标记mul1=a,add1=b，则pushdown中应有sum=sum*a+b
// 如果现在又打上了一个懒标记mul2=c,add2=d，且前面还未处理，则应为(sum*a+b)*c+d=sum*ac+bc+d
// 因此，新的懒标记应当是mul=mul1*mul2,add=add1*mul2+add2

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10;

struct Node {
    int l, r;
    LL sum, mul, add;
} tr[N << 2];

int n, m, p;
int w[N];

void pushup(int u) {
    // 注意每次运算都要取模
    tr[u].sum = (tr[u << 1].sum + tr[u << 1 | 1].sum) % p;
}

// 更新懒标记并更新查询值
void eval(Node& u, int add, int mul) {
    // 更新查询值
    u.sum = ((LL)u.sum * mul + (LL)add * (u.r - u.l + 1)) % p;
    // 更新懒标记，正确处理叠加
    u.mul = (LL)u.mul * mul % p;
    u.add = ((LL)u.add * mul + add) % p;
}

void pushdown(int u) {
    // 传递懒标记
    eval(tr[u << 1], tr[u].add, tr[u].mul);
    eval(tr[u << 1 | 1], tr[u].add, tr[u].mul);
    // 清空u的懒标记
    tr[u].add = 0, tr[u].mul = 1;
}

void build(int u, int l, int r) {
    // 注意mul的初始值为1
    if (l == r) {
        tr[u] = {l, r, w[l], 1, 0};  
        return;
    }
    // sum随便赋值，pushup会修正的
    tr[u] = {l, r, 0, 1, 0};
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

void modify(int u, int l, int r, int add, int mul) {
    if (tr[u].l >= l && tr[u].r <= r) {
        eval(tr[u], add, mul);
        return;
    }
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid) {
        modify(u << 1, l, r, add, mul);
    }
    if (r > mid) {
        modify(u << 1 | 1, l, r, add, mul);
    }
    pushup(u);
}

LL query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) {
        return tr[u].sum;
    }
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    LL sum = 0;
    if (l <= mid) {
        sum += query(u << 1, l, r);
    }
    if (r > mid) {
        sum = (sum + query(u << 1 | 1, l, r)) % p;
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 别忘线段树使用1-index
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    build(1, 1, n);

    cin >> m;
    while (m--) {
        int t, l, r, d;
        cin >> t >> l >> r;
        if (t == 1) {
            cin >> d;
            modify(1, l, r, 0, d);
        } else if (t == 2) {
            cin >> d;
            modify(1, l, r, d, 1);
        } else {
            cout << query(1, l, r) % p << '\n';
        }
    }

    return 0;
}
