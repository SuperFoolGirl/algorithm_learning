// 树的直径

// 先介绍一个直径的模板求法(边权均为1)：
// 遍历过程用DFS或BFS皆可
// 1.从任意一个点a出发，找到距离它最远的点u
// 2.从u出发，找到距离它最远的点v
// 3.u和v之间的距离即为树的直径

// 证明：
// 即证u一定是某条直径的一个端点
// 1.假设bc是树的一条直径，且与au无交点
// 取路径au上一点x，路径bc上一点y。由于树是连通的，因此x与y间必可达
// 对于u是距离a最远的点，因此xu>=xy+yc；否则a的最远点就是c了
// 因此，一定有xu+xy>=yc，显然
// 这样一来，by+yx+xu>=by+yc=bc，而bd又是直径，因此只能取等，即bu=bc
// 证得u一定是某条直径的一个端点
// 2.假设bc是树的一条直径，且与au有交点，设交点为x
// 由于距离a最远的是u，因此ax+xu>=ax+xc，即xu>=xc
// 又因为bc是直径，因此bx+xc>=bx+xu，即xc>=xu
// 综上，xu=xc，即bu=bc，因此u也是某条直径的一个端点



// 下面回到主题，树形DP
// 本题思路比较简单，统计每个点走到叶子节点的最长距离和次长距离，更新答案即可
// 不依赖状态数组存储答案，纯DFS
// 本题是无向树，任何一点都可以作为根。代码中不妨取1为根即可
// 但由于建图需要按无向边来，因此需要避免dfs时重复访问父节点，造成死循环
// 方法：dfs中传入参数fa，表示当前节点的父节点；在遍历邻接表时，如果遇到邻接点是fa，则跳过即可

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10, M = 2 * N;

int n;
int h[N], e[M], ne[M], idx;
int w[M];
int ans;

void add(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

int dfs(int u, int fa) {
    // dist表示从u出发，能到达的最远距离
    int dist = 0;

    // 统计u往下走达到的的最长距离、次长距离
    int d1 = 0, d2 = 0;

    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) {
            continue;
        }
        // 本轮计算出的u向下能走到的最远距离
        int d = dfs(j, u) + w[i];

        // 每轮打擂台，存储u向下能走到的最远距离
        dist = max(dist, d);

        if (d >= d1) {
            d2 = d1;
            d1 = d;
        } else if (d > d2) {
            d2 = d;
        }
    }

    ans = max(ans, d1 + d2);

    return dist;
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

    dfs(1, -1);
    cout << ans << endl;

    return 0;
}
