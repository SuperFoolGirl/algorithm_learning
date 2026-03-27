// 最多只能砍两刀，先砍主要边(树边)，再砍次要边(非树边)
// 注意，如果最后一刀砍掉树边就能使得树不连通，则还需要补一刀非树边
// 也就是说，游戏必须以砍掉非树边+树不连通为结束条件

// 如何将树切成不连通？
// 很简单，切去任意一条边即可；即使是叶子，也会使得叶子成为单独的连通块
// 本题存在“附加边”，这一定会导致树成环
// 下面用一个例子来说明：
// 设边a-b是树中一条边，且a-b在某一环上，这个环是由原树边+附加边s构成的
// 这种情况下，先切a-b，再切s，树就不连通了
// 那么，如何找到这个环呢？结合上一题的视角——只要涉及环，就往"边xy+弧xy=环，找xy的lca"的思路走即可
// 设s的两端为x,y，就满足本题条件了；x,y在寻找lca的过程，一定会遇到同在环上的a-b

// 步骤
// 维护状态数组c，统计所有树边e的信息：砍掉e后，还要砍掉几条非树边，才能使得树不连通
// 枚举所有的m条非树边，对于非树边所在环上的每条树边e，执行c[e]++
// 遍历所有树边e，统计方案数res：
// 1.若c[e]=0，说明砍掉e后树就不连通了，可以砍掉任意非树边，res+=m
// 2.若c[e]=1，说明砍掉e后还需要砍一条非树边(这条边是确定的，即环上的唯一非树边)，res+=1
// 3.若c[e]>1，说明砍掉e后还需要砍多条非树边，res+=0

// 对一个区间同时加一个值，用差分会提高效率
// 对于区间[l,r]都加c，可以在l位置加c，在r+1位置减c；最后对差分数组求前缀和，就得到了每个位置的值
// 那么，下面介绍树上差分：在O(1)时间内为一条路径上的每条边加c
// 首先设置差分数组d，用点来索引；但其为求边权服务
// 对以s为根的子树中的d求和，就能得到s与其父亲之间边的权值
// 方法：d[x]+=c, d[y]+=c, d[lca]-=2c
// 计算的结果是，x-lca-y路径上每条边都+c；可以自己画图验证下
// 老样子，lca问题，还是看作两条路径相加：x->lca和y->lca
// 根据上述定义，这两段路径的总边权为：路径上所有点各自求其d的“树和”，并相加；其中不含lca(路径不涉及lca与其父亲的边)

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 100010, M = 2 * N;

int n, m;
int h[N], e[M], ne[M], idx;
int depth[N], fa[N][17];
int d[N];    // 树上差分数组
int q[N];
int ans;

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

void bfs() {
    memset(depth, 0x3f, sizeof depth);
    depth[0] = 0, depth[1] = 1;    // 依旧无向树，设1为root
    int hh = 0, tt = 0;
    q[0] = 1;

    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (depth[j] > depth[t] + 1) {
                depth[j] = depth[t] + 1;
                q[++tt] = j;

                fa[j][0] = t;
                for (int k = 1; k <= 16; k++) {
                    int anc = fa[j][k - 1];
                    fa[j][k] = fa[anc][k - 1];
                }
            }
        }
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) {
        swap(a, b);
    }

    for (int k = 16; k >= 0; k--) {
        if (depth[fa[a][k]] >= depth[b]) {
            a = fa[a][k];
        }
    }

    if (a == b) {
        return a;
    }

    for (int k = 16; k >= 0; k--) {
        if (fa[a][k] != fa[b][k]) {
            a = fa[a][k];
            b = fa[b][k];
        }
    }

    return fa[a][0];
}

int dfs(int u, int father) {
    // 统计以u为根的子树中所有点的差分和，别忘了加上自己的差分值d[u]
    int res = d[u];
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == father) {
            continue;
        }
        // 统计该子树的差分和s，结果相当于儿子j指向u的边的权值
        // 从这里也能看出来，本dfs会将所有的边都遍历到
        int s = dfs(j, u);
        if (s == 0) {
            ans += m;
        } else if (s == 1) {
            ans++;
        }
        res += s;
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    memset(h, -1, sizeof h);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
        add(b, a);
    }

    // lca预处理
    bfs();

    // 非树边不用存，可以边读边做
    while (m--) {
        int a, b;
        cin >> a >> b;
        int p = lca(a, b);
        // 树上差分
        d[a]++, d[b]++, d[p] -= 2;
    }

    // 自底向上求树上差分和，得到每条边的权值
    // 期间，用ans统计目标边权总和，即为答案
    dfs(1, -1);
    cout << ans << endl;

    return 0;
}
