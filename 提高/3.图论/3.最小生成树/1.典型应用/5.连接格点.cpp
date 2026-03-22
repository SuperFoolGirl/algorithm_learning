// 考虑问题“求将所有点连通的最小边权和”
// 下意识会想求最小生成树
// 但是，如果图中含有负权边，那答案就不是树了
// 极端一点，对于完全图，如果边权都为负，那满足问题的答案应该是整个完全图，而不是mst
// 选用mst算法前，要先看好边权条件

// 对于这种n行m列方格，考虑其边的数量：
// 1.横向边：n行，每行m-1条边，共n*(m-1)条
// 2.竖向边：m列，每列n-1条边，共m*(n-1)条
// 因此，边的数量大致为2mn

// 另外，对于这种方格图，点的坐标是二维的，代码写起来比较麻烦
// 之前已经处理过很多这样的题目了，自行转为一维即可，编号为0~nm-1 / 1~nm
// 具体操作为借助一个二维数组来映射：f({二维坐标}) = 一维编号

// 本题中，边权只有1和2，可以自行控制边的输入顺序，省去排序

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

// N是行列数，M是点数，K是边数
const int N = 1010, M = N * N, K = 2 * M;

int n, m, k;      // k记录边数
int ids[N][N];    // 二维坐标与一维编号的映射

struct Edge {
    // 不需要排序
    int a, b, w;
} e[K];

int p[N];

int find(int x) {
    if (p[x] != x) {
        p[x] = find(p[x]);
    }
    return p[x];
}

void get_edges() {
    // 只考虑非必选边，但其实也可以把必选边加进来
    // 它们在跑kruskal是会被自然过滤
    // 这里主要是因为筛选必选边太麻烦了，所以直接逃课
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
    int dw[] = {1, 2, 1, 2};    // 横向边权为2，竖向边权为1

    // 遍历每个点，枚举它的四个方向来加边
    // 注意，先加竖边，避免排序；因此跑两个for，或最外层嵌套一个for来控制
    for (int z = 0; z < 2; z++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                for (int u = 0; u < 4; u++) {
                    // 注意，这里也需要对u进行控制，以先竖再横
                    if (u % 2 == z) {
                        int x = i + dx[u], y = j + dy[u];
                        if (x < 1 || x > n || y < 1 || y > m) {
                            continue;
                        }

                        int a = ids[i][j], b = ids[x][y], w = dw[u];
                        // 注意，虽然kruskal算法需要无向边，但不需要加两次——它只识别两端点
                        // 格子图+枚举四方向会有大量重复边，注意筛选
                        // 方法：只允许加边e(a,b)，其中a < b
                        if (a < b) {
                            e[k++] = {a, b, w};
                        }
                    }
                }
            }
        }
    }
}

int kruskal() {
    int res = 0;
    for (int i = 0; i < k; i++) {
        int a = find(e[i].a), b = find(e[i].b), w = e[i].w;
        if (a != b) {
            p[a] = b;
            res += w;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 1; i <= n * m; i++) {
        p[i] = i;
    }

    // 映射编号
    for (int i = 1, t = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++, t++) {
            ids[i][j] = t;
        }
    }

    // 读入已存在的边
    int x1, y1, x2, y2;
    while (cin >> x1 >> y1 >> x2 >> y2) {
        int a = ids[x1][y1], b = ids[x2][y2];
        p[find(a)] = find(b);
    }

    // 输入所有边
    get_edges();

    cout << kruskal() << endl;

    return 0;
}
