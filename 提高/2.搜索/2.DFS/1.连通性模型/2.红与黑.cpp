// 无向图，st数组

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 25;

int n, m;
char g[N][N];
bool st[N][N];
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int dfs(int x, int y) {
    // 还是考虑递归树
    // cnt记录以(x,y)为根的子树的结点数
    // 因此最后返回cnt
    // 那么栈底返回的cnt就是以起点为根的子树的结点数了，也就是总的结点数了
    // 这种想法和DP有点像，属于是迁移运用了
    // 由于图存在共享父子的问题，因此用st数组来标记已经访问过的结点，避免重复访问

    // 当然，也可以直接维护全局变量，那样更简单
    int cnt = 1;
    st[x][y] = true;

    // 本题把“出口”写在扩展中，因为本题的出口很像是“剪枝”
    for (int i = 0; i < 4; i++) {
        int a = x + dx[i], b = y + dy[i];

        if (a < 0 || a >= n || b < 0 || b >= m) {
            continue;
        }

        if (st[a][b]) {
            continue;
        }

        // 出口
        if (g[a][b] != '.') {
            continue;
        }

        cnt += dfs(a, b);
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    while (cin >> m >> n, n || m) {
        // 多组数据，别忘清空辅助数组信息
        memset(st, false, sizeof st);
        for (int i = 0; i < n; i++) {
            cin >> g[i];
        }

        int x, y;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (g[i][j] == '@') {
                    x = i;
                    y = j;
                    break;
                }
            }
        }

        cout << dfs(x, y) << endl;
    }

    return 0;
}
