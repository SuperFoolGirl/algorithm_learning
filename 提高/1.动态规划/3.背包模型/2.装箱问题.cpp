// 要求剩余体积最小，也就是装得最多
// 因此体积占据了价值的生态位
// 还是01背包模型，把价值也看成体积即可
// 即w数组与v数组是一致的

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

int n, m;
int f[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i <= n; i++) {
        int v;
        cin >> v;
        for (int j = m; j >= v; j--) {
            f[j] = max(f[j], f[j - v] + v);
        }
    }

    cout << m - f[m] << endl;

    return 0;
}
