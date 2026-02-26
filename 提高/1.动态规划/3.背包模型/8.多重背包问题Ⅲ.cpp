// 用单调队列来优化多重背包，具体原理在基础课中有讲

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

int n, m;
int f[N], g[N];  // g用于辅助表示滚动数组
int q[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        // 体积 价值 数量
        int v, w, s;
        cin >> v >> w >> s;
        // 将上一轮的数据复制到g中，作为当前轮的基础
        memcpy(g, f, sizeof f);
        // 枚举余数，即j-ns的结果。这里用j来表示。最小取0(s整除v)，最大取v(n取0)
        for (int j = 0; j < v; j++) {
            int hh = 0, tt = -1;
            for (int k = j; k <= n; k += v) {
                // 判断单调队列左边界过期，窗口大小为s个v
                if (hh <= tt && q[hh] < k - s * v) {
                    hh++;
                }
                // 计算当前区间的最优值
                if (hh <= tt) {
                    f[k] = max(f[k], g[q[hh]] + (k - q[hh]) / v * w);
                }
                // 维护单调
                while (hh <= tt && g[q[tt]] - (q[tt] - j) / v * w <= g[k] - (k - j) / v * w) {
                    tt--;
                }
                q[++tt] = k;
            }
        }
    }

    cout << f[m] << endl;

    return 0;
}
