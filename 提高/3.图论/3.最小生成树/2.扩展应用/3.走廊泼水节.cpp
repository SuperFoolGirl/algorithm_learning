// 本题要求把树补成完全图，且完全图的最小生成树是原树且唯一
// 完全图的边数为C(n,2)

// 1.将树中所有的边升序排序，先去掉这些边，孤立地看这n个点
// 2.开始从小到大加入边，此时也是逐渐合并集合的过程(kruskal的连通块思想)；根据本题的要求，每次合并集合，都需要将新集合补成完全图——合并两个集合时，将两个集合的所有点各自连接，如果两个集合的点分别为x,y，则需要加入x*y-1条边(原本mst有一条边)
// 3.将所有的点都合并成一个集合时，最后就形成了完全图

// 证明正确性：
// 对于第i轮循环，此时要处理边{ai,bi,wi}；此时a和b各自处于一个集合(连通块)(若ab连通，那么这条边就会被跳过了)，下面将要合并ab两个集合，并把这个集合补成完全图；两个集合互相补边的值，与wi有关：
// 1.新边<wi: 此时不合理。连成完全图形成环，如果新边<wi，那么wi被新边替代后会得到更小的生成树，与题目要求矛盾(这里如readme的证明相似，但不完全一样；可以画图理解)
// 2.新边=wi: 最后的生成树虽然权值一样，但不满足唯一。不合理
// 3.因此，只能满足新边严格大于wi，即新边>=wi+1。根据题目要求，需要新加的边权和最小，那么很自然地想到所有加边都取下限wi+1。设这种方案下总权值为s，下面证明这个方案的正确性，即已知res>=s，证明可以取等：
// 若正确，则证明mst唯一即可，用反证。若mst不唯一，则另一棵mst'至少有一条边与mst不同。设第一条不同的边为e...

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 6000 + 10;

struct Edge {
    int a, b, w;
    bool operator<(const Edge& t) const {
        return w < t.w;
    }
} e[N];
int n;
int p[N], sz[N];  // 本题需要维护集合的大小

// p[]是找父亲，find函数是找祖宗
int find(int x) {
    if (p[x] != x) {
        p[x] = find(p[x]);
    }
    return p[x];
} 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n - 1; i++) {
            cin >> e[i].a >> e[i].b >> e[i].w;
        }

        sort(e, e + n - 1);
        for (int i = 1; i <= n; i++) {
            p[i] = i;
            sz[i] = 1;
        }

        int res = 0;
        for (int i = 0; i < n - 1; i++) {
            int a = find(e[i].a), b = find(e[i].b), w = e[i].w;
            if (a != b) {
                res += (sz[a] * sz[b] - 1) * (w + 1);
                sz[b] += sz[a];    // 只有祖宗的size是有效数据
                p[a] = b;
            }
        }

        cout << res << endl;
    }

    return 0;
}
