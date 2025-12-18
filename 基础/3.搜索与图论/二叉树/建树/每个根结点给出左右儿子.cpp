// 最简单的一种，根本不需要add函数

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10;

// 0表示无左右子节点
struct Node {
    int l;
    int r;
} tr[N];

int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    // 输入n行，每行给出一个节点的左右子节点
    // 0表示无子节点，这里输入与初始化吻合
    for (int i = 1; i <= n; ++i) {
        int l, r;
        cin >> l >> r;
        tr[i].l = l;
        tr[i].r = r;
    }

    return 0;
}
