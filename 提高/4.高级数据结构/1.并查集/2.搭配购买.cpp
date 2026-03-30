// 01背包+并查集
// 凡是在一个集合里的，要买都得买
// 然后将整个集合的物品视为一个物品，进行01背包

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 10010;

int n, m, vol;
int v[N], w[N];
int p[N];
int f[N];

int find(int x) {
    if (p[x] != x) {
        p[x] = find(p[x]);
    }
    return p[x];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m >> vol;
    for (int i = 1; i <= n; i++) {
        p[i] = i;
    }

    for (int i = 1; i <= n; i++) {
        cin >> v[i] >> w[i];
    }

    while (m--) {
        int a, b;
        cin >> a >> b;
        int pa = find(a), pb = find(b);
        if (pa != pb) {
            v[pb] += v[pa];
            w[pb] += w[pa];
            p[pa] = pb;
        }
    }

    // 01背包
    for (int i = 1; i <= n; i++) {
        // 只有根结点才有意义
        if (p[i] == i) {
            for (int j = vol; j >= v[i]; j--) {
                f[j] = max(f[j], f[j - v[i]] + w[i]);
            }
        }
    }

    cout << f[vol] << endl;

    return 0;
}
