// 区间DP内容
// 1. 环形区间改链
// 2. 求方案数
// 3. 与高精度结合
// 4. 二维区间DP

// 环形石子合并，相当于首尾也可以合并
// 下面考虑将问题直观化：
// 一共有n堆石子围成一个圆；若要合并，就在两堆石子间连线
// 可以将这个过程视为并查集的合并
// 最后，一定会有一个缺口，因为只连n-1条线
// 那么，一个朴素的想法：枚举缺口的位置，就可以转为链式区间DP问题
// 不过分析时间复杂度后，会发现枚举缺口的时间复杂度为O(n)，区间DP的时间复杂度为O(n^3)，总时间复杂度为O(n^4)，无法接受

// 下面介绍普遍的优化方法：
// 用二倍链条来模拟环形。这是处理环形问题的基本方法
// 如果缺口在2-3之间，对应到第一个2和第二个3
// 随意选择一个n区间即可
// 代码实现：
// 1. 迭代式
// for长度len->for起点l->终点r=l+len-1->枚举分割点k
// 2. 记忆化搜索

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 410, INF = 0x3f3f3f3f;

int n;
int s[N], w[N];
int f[N][N], g[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        w[i + n] = w[i];
    }

    for (int i = 1; i <= 2 * n; i++) {
        s[i] = s[i - 1] + w[i];
    }

    memset(f, 0x3f, sizeof f);
    memset(g, -0x3f, sizeof g);

    // 只会用到长度为n的序列，不用遍历到2n
    // len应当从1开始枚举，len为1时根据定义进行初始化
    for (int len = 1; len <= n; len++) {
        for (int l = 1; l + len - 1 <= 2 * n; l++) {
            int r = l + len - 1;
            // 初始化
            if (len == 1) {
                f[l][r] = 0;
                g[l][r] = 0;
            } else {
                // 枚举分割点k
                // 注意k的枚举方式可以确保lr均有机会独立
                for (int k = l; k < r; k++) {
                    f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r] + s[r] - s[l - 1]);
                    g[l][r] = max(g[l][r], g[l][k] + g[k + 1][r] + s[r] - s[l - 1]);
                }
            }
        }
    }

    int minv = INF, maxv = -INF;
    for (int i = 1; i <= n; i++) {
        minv = min(minv, f[i][i + n - 1]);
        maxv = max(maxv, g[i][i + n - 1]);
    }

    cout << minv << endl << maxv << endl;

    return 0;
}
