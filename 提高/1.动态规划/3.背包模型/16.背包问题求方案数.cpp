// 并非是属性为cnt这么简单
// 而是最优解的方案数
// 也就是说，本题有很多种得到最优解的方案
// 思路是用一个辅助数组，并行地进行状态转移

// 本题以01背包为例
// 用g(i,j)来维护最优解数目
// 状态表示：g(i,j)表示f(i,j)取最优解的方案数
// 其实就是纯模拟的过程
// 对于f(i,j) = max{ f(i-1,j) + f(i-1,j-v[i]) }
// 1. 若f(i-1,j) > f(i-1,j-v[i]) + w[i]，则g(i,j) = g(i-1,j)
// 2. 若f(i-1,j) < f(i-1,j-v[i]) + w[i]，则g(i,j) = g(i-1,j-v[i])
// 3. 若f(i-1,j) = f(i-1,j-v[i]) + w[i]，则g(i,j) = g(i-1,j) + g(i-1,j-v[i])
// 显然g需要初始化，方式参考readme，其实就是cnt属性的初始化方式

// 但是，f的状态表示需要修改，变为“恰好模型”
// 这样会更加好算，不用考虑容斥原理问题
// 这里可以展开说一下
// 对于f，属性为max，集合划分只讲究“不漏”
// 但是对于g，属性为cnt，还要遵循“不重”
// 在至多模型下，f划分无法做到“不重”，因此需要改为恰好模型
// 在恰好模型下，即使属性是max/min，划分时也能做到不重
// 以f(i,j) = max{ f(i-1,j) + f(i-1,j-v[i]) }为例
// 在至多模型下，f(i-1,j)和f(i-1,j-v[i])这两个集合是有交集的，因此g(i,j) = g(i-1,j) + g(i-1,j-v[i])会有重复计数的问题
// 而恰好模型从根本上杜绝了重复的性质

// 由于只求最优解方案数，因此只需要i=n的数据，可以降维；同时干掉v/w数组
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10, MOD = 1e9 + 7;

int n, m;
int f[N], g[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;

    // 参考readme中提到的恰好模型初始化方法：(自然省略对0的初始化)
    // f属性为max，f[0]=0, f[1~m]=-∞
    // g属性为cnt，g[0]=1, g[1~m]=0
    // 可以发现f的状态转移方程和至多模型的01背包完全一样，区别只在于初始化和寻找最终答案
    memset(f, -0x3f, sizeof f);
    f[0] = 0;
    g[0] = 1;

    for (int i = 0; i < n; i++) {
        int v, w;
        cin >> v >> w;
        for (int j = m; j >= v; j--) {
            int maxv = max(f[j], f[j - v] + w);
            int cnt = 0;
            if (maxv == f[j]) {
                cnt += g[j];
            }
            if (maxv == f[j - v] + w) {
                cnt += g[j - v];
            }
            f[j] = maxv;
            g[j] = cnt % MOD;
        }
    }

    // 注意，在恰好模型下，f[m]并不一定是最大价值
    // 在至多模型下，f[m]表示花费最多是m的最大价值；在恰好模型下，f[m]表示花费恰好是m的最大价值
    // 显然二者不等价，前者范围更大(这种对“不重”的抛弃使得它能扩大了范围)
    // 另外，初始化也不同，使得在两种模型下，f的值也可能不同
    int res = 0;
    for (int i = 0; i <= m; i++) {
        res = max(res, f[i]);
    }
    
    // 现在找到最大值f[i]了，但不确定一共有几个
    // 可能存在f[x] = f[y] = res的情况，因此需要遍历一遍f数组，找到所有等于res的f[i]，将对应的g[i]加起来
    int cnt = 0;
    for (int i = 0; i <= m; i++) {
        if (f[i] == res) {
            cnt = (cnt + g[i]) % MOD;
        }
    }

    cout << cnt << endl;

    return 0;
}
