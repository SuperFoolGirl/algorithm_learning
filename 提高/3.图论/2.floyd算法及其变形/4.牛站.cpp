// floyd的倍增算法

// 本题并没有涉及floyd算法，而是借助其状态表示的外形，给予新的状态表示方法来解决其他问题

// 本题结点编号并非顺序，而是给定一个大范围，从中任意取数编号
// 因此需要离散化

// 本题依然是借助DP，或者说集合划分思想
// f(a+b,i,j): 表示从i到j，恰好经过a+b条边的最短路径
// 状态转移：
// 对于d(a+b,i,j)，想要进行划分，枚举中间点k即可
// d(a+b,i,j) = min{d(a,i,k) + d(b,k,j)}, k∈[1,n]

// 下面再重复一下之前提到的思想：最短路的可加性
// 如果路径确定不会走重复的点，那么路径的各段是独立的、可加的
// 这种情况下，路径加法满足结合律，但不满足交换律
// 可以发现，这种计算模式，特别像矩阵乘法——可结合不可交换
// 只要满足结合律，就可以用倍增思想——即快速幂的方式来优化(矩阵乘法也可以用快速幂优化)
// 这里是把k直接拆分成二进制数，而不是多重背包二进制优化那样，一直上1，留下r单独打包

// 如果正常计算f(k,i,j)，k是“一步步推进的”
// 如果用上述方法，2^p来逼近k，那么效率就会提升
// 即先求f(1,i,j)，再求f(2,i,j)，再求f(4,i,j)，再求f(8,i,j)...
// 权值分别为2^0, 2^1, 2^2, 2^3...
// 把k表示成二进制数的形式，k = 2^p1 + 2^p2 + ... + 2^pm

// 本题离散化不依赖排序(如前缀和等事务)，因此可以用u_map

#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_map>

using namespace std;

const int N = 210;

int k, n, m, S, E;
// g用于计算f()
int g[N][N];
int res[N][N];
unordered_map<int, int> ids;

// 每加一条边，重新跑一遍"floyd"
void mul(int c[][N], int a[][N], int b[][N]) {
    // 避免每次进入函数都在栈上分配数组，相当于全局变量
    static int temp[N][N];
    memset(temp, 0x3f, sizeof temp);

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                temp[i][j] = min(temp[i][j], a[i][k] + b[k][j]);
            }
        }
    }

    memcpy(c, temp, sizeof temp);  // 参数3一定要是temp，因为c是指针
}

void qmi() {
    // 一条边都不经过的情况下，i可以到i，距离为0
    memset(res, 0x3f, sizeof res);
    for (int i = 1; i <= n; i++) {
        res[i][i] = 0;
    }

    while (k) {
        if (k & 1) {
            mul(res, res, g);  // res = res * g
        }
        mul(g, g, g);  // g = g * g
        k >>= 1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> k >> m >> S >> E;
    if (!ids.count(S)) {
        ids[S] = ++n;
    }
    if (!ids.count(E)) {
        ids[E] = ++n;
    }
    S = ids[S], E = ids[E];

    // 经过一条边的情况下，i无法到i，因此都初始化为INF
    // 下面的循环里会输入经过一条边的情况下的边权，这里只是初始化
    memset(g, 0x3f, sizeof g);

    while (m--) {
        int a, b, c;
        cin >> c >> a >> b;
        // 本题中需要离散化的对象是点编号
        // 离散化编号从1开始
        if (!ids.count(a)) {
            ids[a] = ++n;
        }
        if (!ids.count(b)) {
            ids[b] = ++n;
        }
        a = ids[a], b = ids[b];
        
        g[a][b] = g[b][a] = min(g[a][b], c);
    }

    qmi();

    cout << res[S][E] << endl;

    return 0;
}
