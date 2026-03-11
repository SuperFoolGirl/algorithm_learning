// 本题要求求出任意两点间的最短距离
// 也就是n(n-1)/2个结果
// 然后在这些结果里取最小值

// 思考：如何加速求解过程？
// 如果这是有向图，那Floyd直接秒了
// 因此还是借助上题的思路，统计每个点向下走到叶子结点的最长距离
// 但问题是，任意两点间的距离，可不一定只是向下走就能到达，总会需要向上走的
// 上一题的思路只能处理向下走，向上走需要额外的处理

// 我们并不需要明确求出点u到其他任意点的距离，我们只需要知道点u到哪个点的距离最远就可以了
// 上一个题的思路，我们可以明确求出，在以u为根的子树中，哪个点里u最远
// 用down来记录向下能走到的最远距离，up来记录向上能走到的最远距离；最后二者取max，就是u到其他任意点的最远距离
// 设当前点为u，父结点是v，目标点是w；uw的某条路径中需要经过v
// 这里补充下：如果u向下能走到的点w，不可能还有经过其父v到达w的路径，否则就成环了
// u下面的点，指的是以u为根的子树中的其他点集；此范围外的点都需要向上走才能走到，包括走到其兄弟、祖宗
// u向上走到v后，v也有两大种走法：
// 1.继续向上走，将球继续传
// 2.向下走
//   2.1 往下走又经过u
//   2.2 往下走不经过u
// 显然，2.2是在无向图dfs中想要避免的情况
// 因此，如果v往下走会经过u，则不要这条路，返回次大值；如果v往下走不会经过u，则返回它作为最大值即可
// 不可能最大值和次大值都来自u，因为回忆down的计算，来源是每个子结点；一个子结点只能提供一份数据
// 即d[v]=max(d[v], d[j]+w[i])，j是v的子结点，而j=u只有一次机会

#include <algorithm>
#include <cstring>
#include <iostream>


using namespace std;

const int N = 10010, M = 2 * N, INF = 0x3f3f3f3f;

int n;
int h[N], e[M], ne[M], w[M], idx;
// d1存储u往下走能达到的最长距离；d2存储u往下走能达到的次长距离
int d1[N], d2[N];
// up存储u往上走能达到的最长距离
int up[N];
// p1存储u往下走能达到的最长距离的子节点；p2存储u往下走能达到的次长距离的子节点
int p1[N], p2[N];

void add(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

// 子结点->父结点
int dfs_d(int u, int fa) {
    if (h[u] == -1) {
        return 0;
    }

    // max类型初始化
    d1[u] = d2[u] = -INF;

    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) {
            continue;
        }
        int d = dfs_d(j, u) + w[i];
        if (d >= d1[u]) {
            d2[u] = d1[u];
            d1[u] = d;
            p2[u] = p1[u];
            p1[u] = j;
        } else if (d > d2[u]) {
            d2[u] = d;
            p2[u] = j;
        }
    }

    return d1[u];
}

// 父结点->子结点
int dfs_u(int u, int fa) {
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) {
            continue;
        }
        // 研究j向上走的最大值
        if (p1[u] == j) {    // 2.2 u向下走的最长距离经过j，此时要舍弃这条路，否则会出现j->u->j
            up[j] = max(up[u], d2[u]) + w[i];
        } else {             // 2.1 u向下走的最长距离不经过j，此时可以使用这条路
            up[j] = max(up[u], d1[u]) + w[i];
        }

        dfs_u(j, u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);
    }

    // 统计每个点向下走能达到的最长距离和次长距离
    dfs_d(1, -1);

    // 统计每个点向上走能达到的最长距离
    // 但是函数内部并不是让u往父亲那里走，而是从父亲的角度去看u
    dfs_u(1, -1);

    int res = INF;
    for (int i = 1; i <= n; i++) {
        // max求每个点到其他任意点的最远距离，min求所有点的最远距离的最小值
        res = min(res, max(d1[i], up[i]));
    }
    cout << res << endl;

    return 0;
}
