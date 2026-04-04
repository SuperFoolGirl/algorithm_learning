// 区间修改，单点查询
// 本题中，将tr视为差分数组
// 差分数组求前缀和可得到原数组

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 100010;

int n, m;
int a[N];
LL tr[N];

int lowbit(int x) {
    return x & -x;
}

void add(int x, int c) {
    for (int i = x; i <= n; i += lowbit(i)) {
        tr[i] += c;
    }
}

int sum(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) {
        res += tr[i];
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        add(i, a[i] - a[i - 1]);  // 构造差分数组
    }

    while (m--) {
        char op[2];  // 操作占1个，另一个用来处理空白字符，避免自己getchar
        int l, r, d;
        cin >> op >> l;
        if (*op == 'C') {
            cin >> r >> d;
            // 区间修改
            add(l, d);
            add(r + 1, -d);
        } else {
            // 查询
            cout << sum(l) << '\n';
        }
    }

    return 0;
}
