#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

struct Node {
    int l = -1;
    int r = -1;
} tr[N];

int n, res;

void add(int a, int b) {
    if (tr[a].l == -1) {
        tr[a].l = b;
    } else {
        tr[a].r = b;
    }
}

// 虽然是求直径，但这个函数的作用是返回t子树的高度
// 直径就是通过高度求的
int diameter(int t) {
    if (t == -1) {
        return 0;
    }

    int lh = diameter(tr[t].l);
    int rh = diameter(tr[t].r);

    res = max(res, lh + rh + 1);

    return max(lh, rh) + 1;
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

    diameter(1);

    cout << res << endl;

    return 0;
}
