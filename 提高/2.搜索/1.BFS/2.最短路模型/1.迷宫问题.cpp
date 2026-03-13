// 记录具体路线
// 图论来了直接fa数组
// 不过fa命名适应树形结构，这里用pre
// 同时pre还能兼顾st的访问记录功能

// 顺便说一下最短路的维护
// 固然可以维护dist状态
// 但也可以根据bfs的层数，类似层序遍历
// 每扩展一层，最外层统计步数+1

#include <iostream>
#include <cstring>
#include <algorithm>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int N = 1010;

int n;
int g[N][N];
PII q[N * N];
PII pre[N][N];
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

void bfs(int sx, int sy) {
    int hh = 0, tt = 0;
    q[0] = {sx, sy};
    memset(pre, -1, sizeof pre);
    // 起点初始化无所谓，只要能表示“访问过”即可，不是-1就行
    pre[sx][sy] = {0, 0};

    while (hh <= tt) {
        PII t = q[hh++];

        for (int i = 0; i < 4; i++) {
            int a = t.x + dx[i], b = t.y + dy[i];
            if (a < 0 || a >= n || b < 0 || b >= n) {
                continue;
            }
            if (g[a][b]) {
                continue;
            }
            if (pre[a][b].x != -1) {
                continue;
            }

            q[++tt] = {a, b};
            pre[a][b] = t;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> g[i][j];
        }
    }

    // 为了避免倒序输出路径，直接从终点开始bfs
    bfs(n - 1, n - 1);

    // 从终点向起点输出路径
    PII t = {0, 0};
    while (true) {
        cout << t.x << ' ' << t.y << endl;
        if (t.x == n - 1 && t.y == n - 1) {
            break;
        }
        t = pre[t.x][t.y];
    }

    return 0;
}
