// 本题本质上不是环形DP
// 给多边形的每个顶点编号，整个多边形表示为f(1,n)
// 在多边形上任意作出一个三角形，这个三角形可以把整个多边形分成三部分：
// 左边的多边形、当前三角形、右边的多边形
// 由这个重要性质，可以得到答案
// 从这里发现，在解题上，DP的思考方式和递归算法基本一致，当然这也是理所应当的

// 状态表示 f(l,r)
// 集合：所有将(l,l+1),(l+1,l+2),...,(r-1,r)(r,l)这个多边形划分成三角形的方案
// 属性：min
// 状态计算
// f(l,r) = min{ f(l,k)+f(k,r)+w[l]*w[k]*w[r] }

// 本题需要高精度，不过高精度的解法，应该是：先不考虑高精度，写出普通解法后，再换成高精度接口

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 55, M = 35, INF = 0x3f3f3f3f;

int n;
int w[N];
int f[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    // 根据题目，顶点个数为3开始才有意义，因此len从3开始枚举
    for (int len = 3; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            f[l][r] = INF;
            for (int k = l + 1; k < r; k++) {
                f[l][r] = min(f[l][r], f[l][k] + f[k][r] + w[l] * w[k] * w[r]);
            }
        }
    }

    cout << f[1][n] << endl;

    return 0;
}
