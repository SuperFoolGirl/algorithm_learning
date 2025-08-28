// 282
// 状态表示：
// 集合：f[i,j]表示所有 将第i堆石子到第j堆石子 合并成一堆石子的方式。则答案为f[1,n]
// 属性：min
// 状态计算：
// 最后一步，一定是两堆合并为一堆（区间内的石子要两两合并）
// 因此状态可以划分为 1,k-1 | 2,k-2 | ... | k-1,1 ，表示最后一步的合并情况
// 但是要注意，不一定是单堆石子合并过去，可能是已经合并过的石子 合并到 另一堆合并过的石子
// 因此上面说的状态划分其实是“分割线”，以 3,k-3 为例，左边是3堆石子，右边是k-3堆石子，二者合并
// 状态转移方程：f[i,j] = min(f[i,k] + f[k+1,j] + s[j] - s[i-1])，其中k为分割点，s为前缀和，表示最后一步的代价
// k范围 [i,j-1]，保证两边至少各有一堆石子

// 注意，这种“考虑最后一步”的思路，初学dp时讲过。注意回顾以前的方法

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10;

int n;
int s[N];
int f[N][N];

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }

    for (int i = 1; i <= n; i++) {
        s[i] += s[i - 1];
    }

    // 枚举所有区间的手法
    // 外层枚举区间长度，内层枚举起点终点
    for (int len = 2; len <= 2; len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int l = i, r = i + len - 1;
            f[l][r] = 1e9; // 初始化为无穷大，从而使得下面状态转移方程能取最小值
            for (int k = l; k < r; k++) {
                f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r] + s[r] - s[l - 1]);
            }
        }
    }

    cout << f[1][n] << endl;

    return 0;
}
