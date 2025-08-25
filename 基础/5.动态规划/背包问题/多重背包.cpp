// 每个物品i有各自的选择次数限制s[i]
// 这里用到二进制优化法，具体原理请回顾视频

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10;

int w[N], v[N], f[N];
int n, m;

int main() {
    cin >> n >> m;

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        int a, b, s;
        cin >> a >> b >> s;
        int k = 1;    // 二进制的起始，即2^0
        // 下面要用二进制的方式表示数s
        while (k <= s) {
            cnt++;
            v[cnt] = a * k;
            w[cnt] = b * k;
            s -= k;
            k *= 2;
        }
        if (s > 0) {    // 二进制最后的收尾，不规则，只有一次
            cnt++;
            v[cnt] = a * s;
            w[cnt] = b * s;
        }
    }

    n = cnt; // cnt为二进制计数的位数

    // 至此，下面就是标准的01背包问题了
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= v[i]; j--) {
            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }
    }

    cout << f[m] << endl;

    return 0;
}
