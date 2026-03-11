// 本题是“有依赖的背包问题”的简化版
// 设树枝两端连接结点u,v，其中u是v的父结点
// 将结点看成物品，把需要保留的树枝视为背包容量
// 如果想保留v，那么必须保留u
// 但本题是有边权的；背包问题中，物品与价值一一对应；本题作为图，权不在点上，而在边上
// 众所周知，树的边数为n-1
// 因此，把边权直接分配到点上即可；对于u->v，把权重w分配给v。这样，只有根结点上没有权重
// 记住这种图论上的边权点权转化的技巧
// 回到题目，在“有依赖的背包问题”模型下，根结点必须被选择
// 题目要求保留q根树枝，实际上就是保留q个被转移了权重的点+1个无权的根结点，是可以对应上的

// 不过，舍弃这种思路，还是考虑树形DP来解决。不过也是依赖于分组背包
// 状态表示 f(i,j)
// 集合：所有以i为根的树中，选择j条边所能保留的苹果数量
// 属性：max
// 状态计算
// 还是老思路，将结点u的k个子结点的保留情况作为“分组”，保留0个、1个、...、k个作为物品，只能选择一种情况
// 回忆：避免了2^k枚举子结点的选择情况
// f(i,j) = max{ f(i,j-k-1)+f(son,k)+w[i] }，其中son为i结点的子结点，k为枚举son所占用的体积

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110, M = 2 * N;

int n, m;
int h[N], e[M], ne[M], w[M], idx;
int f[N][N];

void add(int a, int b, int c) {
    e[idx] = b;
    ne[idx] = h[a];
    w[idx] = c;
    h[a] = idx++;
}

void dfs(int u, int fa) {
    // 枚举物品组
    for (int i = h[u]; i != -1; i = ne[i]) {
        int son = e[i];
        if (son == fa) {
            continue;
        }
        dfs(son, u);
        // 当前儿子的值已经计算出来了，可以枚举体积了
        for (int j = m; j >= 0; j--) {
            // 枚举物品
            for (int k = 0; k <= j - 1; k++) {
                // son本身占用k条边，u->son占用1条边(权值为w[i])，因此j-k-1条边留给u结点
                f[u][j] = max(f[u][j], f[u][j - k - 1] + f[son][k] + w[i]);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);
    }

    // 根据题目描述，1为根结点；有向图需要fa参数防死循环
    dfs(1, -1);

    cout << f[1][m] << endl;

    return 0;
}
