// 区间修改，区间查询

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 100010;

int n, m;
LL tr1[N];  // 维护b[i]
LL tr2[N];  // 维护i*b[i]
int a[N];

int lowbit(int x) {
    return x & -x;
}

// add/sum操作都有二义性，需要传参来区分是对tr1还是tr2进行操作
void add(LL tr[], int x, LL c) {
    for (int i = x; i <= n; i += lowbit(i)) {
        tr[i] += c;
    }
}

LL sum(LL tr[], int x) {
    LL res = 0;
    for (int i = x; i; i -= lowbit(i)) {
        res += tr[i];
    }
    return res;
}

// 求区间[1,x]的前缀和
LL prefix_sum(int x) {
    return sum(tr1, x) * (x + 1) - sum(tr2, x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        int b = a[i] - a[i - 1];
        add(tr1, i, b);
        add(tr2, i, (LL)b * i);
    }

    while (m--) {
        char op[2];
        int l, r, d;
        cin >> op >> l >> r;
        if (*op == 'Q') {
            cout << prefix_sum(r) - prefix_sum(l - 1) << '\n';
        } else {
            cin >> d;
            // 注意两个树状数组都要修改
            add(tr1, l, d), add(tr2, l, l * d);
            add(tr1, r + 1, -d), add(tr2, r + 1, (r + 1) * -d);
        }
    }

    return 0;
}
