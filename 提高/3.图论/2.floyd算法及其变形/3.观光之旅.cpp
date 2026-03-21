// 求最小环

// 用集合的视角来考虑问题
// 将所有的环视为集合，进行划分
// 分类依据：环上编号最大点的编号

// 以floyd的k循环为上述“分类编号”
// 如何求出第k类呢？
// 枚举所有点对(i,j)，需要满足i->k和k->j有边
// 环长度为d(i,j)+w(i,k)+w(k,j)
// 但其实d(i,j)是已知的——存储在d(k-1,i,j)中，藏在滚动数组里了
// 另外，回忆floyd的DP定义：d(k-1,i,j)表示只允许经过编号<=k-1的点的最短路长度
// 恰好于题目要求一致，保证i->j路径上不会出现k
// 因此，k状态可以由k-1状态转移而来
// 这里需要指出：floyd本质还是求最短路，本题求最小环属于“附加操作”
// 因此，非负环图中，floyd求出任意最短路，一定满足不会重复经过某个点

// 另外本题还需要求具体方案——floyd记录具体方案
// 方法：和DP一样，在状态转移时记录
// 记录d[i][j]的转移：d[i][j] = d[i][k] + d[k][j]，则是由k转移而来，且满足k是i->j路径上编号最大的点
// 还原时，可以递归处理：将d(i,j)写成d(i,k)+d(k,j)，一直分解到基元；可行性基于上面说的“最短路不会重复经过某个点”

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110, INF = 0x3f3f3f3f;

int n, m;
int d[N][N], w[N][N];
int pos[N][N];  // 辅助记录具体方案
int path[N], cnt;  // 存储具体方案，cnt用于索引环中的点
int res = INF;     // 记录最小环的长度

void get_path(int i, int j) {
    if (pos[i][j] == 0) {
        // 说明i->j没有中转点，直接相连
        return;
    }

    int k = pos[i][j];
    // 递归处理i->k和k->j
    get_path(i, k);
    path[cnt++] = k;  // 根据函数定义，k没有被get_path(i,k)处理，因此这里自行处理
    get_path(k, j);
}

void floyd() {
    // dest, src, bytes needed for copy
    memcpy(d, w, sizeof d);

    for (int k = 1; k <= n; k++) {
        // 此处求最小环，滚动数组仍保留k-1层的数据
        // 注意k-1层的最短路数据，经过的最大点是k-1，不要越界枚举
        // 由于是无向图，考虑到对称性，j不需要从小于i的部分枚举，否则会重复枚举
        for (int i = 1; i < k; i++) {
            for (int j = i + 1; j < k; j++) {
                // 由于w被初始化为INF，因此计算有可能爆int
                if ((long long)d[i][j] + w[i][k] + w[k][j] < res) {
                    res = d[i][j] + w[i][k] + w[k][j];
                    cnt = 0;  // 答案被更新，重新记录方案
                    // 把所有点放到path中
                    path[cnt++] = k;
                    path[cnt++] = i;
                    get_path(i, j);  // 处理i->j上除了i和j以外的点
                    path[cnt++] = j;
                }
            }
        }
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (d[i][j] > d[i][k] + d[k][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    pos[i][j] = k;  // 记录转移点
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    memset(w, 0x3f, sizeof w);
    for (int i = 1; i <= n; i++) {
        w[i][i] = 0;
    }

    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        // 邻接矩阵处理重边
        w[a][b] = w[b][a] = min(w[a][b], c);
    }

    floyd();

    if (res == INF) {
        cout << "No solution." << endl;
    } else {
        for (int i = 0; i < cnt; i++) {
            cout << path[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
