// 环形问题只需要考虑线性解法，然后把代码换成环形即可，就是加点东西
// 以样例(2,3)(3,5)(5,10)(10,2)为例
// 记作 2 3 5 10 2，做类矩阵乘法
// 从头到尾整个计算记作 f(1,5)

// 状态表示 f(l,r)
// 集合：所有将[l,r]合并成一个柱子的方式
// 属性：max
// 状态计算
// 最后一个不同点，在于最后一步的合并。枚举分界线即可，都是一样的
// 不同点在于分界线意义的不同；石子合并中k是作为石子中的一个代表，只能用一次
// 而根据本题题意(矩阵乘法性质)，k可以用两次，同时属于两边
// 通俗地说，分界点切在点上，而不是边上
// f(l,r) = max{ f(l,k)+f(k,r)+w[l]*w[k]*w[r] }

// 改为环形，要如何考虑矩阵乘法性质呢？
// 扩容2倍后，枚举的区间应当为n+1，从第一个x开始，到第二个x结束

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 210;

int n;
int w[N];
int f[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        w[i + n] = w[i];
    }

    // 迭代法，注意长度为n+1
    // len初始化应从3开始，这样才有意义
    for (int len = 3; len <= n + 1; len++) {
        for (int l = 1; l + len - 1 <= 2 * n; l++) {
            int r = l + len - 1;
            // 区间低于3无意义，全都是0，这里k起点为l或l+1都一样
            // 区间长度小于3的部分全都是在初始化为0
            for (int k = l + 1; k < r; k++) {
                f[l][r] = max(f[l][r], f[l][k] + f[k][r] + w[l] * w[k] * w[r]);
            }
        }
    }

    int res = 0;
    for (int i = 1; i <= n; i++) {
        res = max(res, f[i][i + n]);
    }
    cout << res << endl;

    return 0;
}
