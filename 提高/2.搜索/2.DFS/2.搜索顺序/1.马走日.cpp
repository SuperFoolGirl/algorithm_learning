// 无向图，st数组
// 本题开始求方案数了，即外部搜索，st数组需要加入恢复现场了

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 10;

int n, m;
bool st[N][N];
int ans;
int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

void dfs(int x, int y, int cnt) {
    // 出口
    if (cnt == n * m) {
        ans++;
        return;
    }

    st[x][y] = true;
    for (int i = 0; i < 8; i++) {
        int a = x + dx[i], b = y + dy[i];
        // 入栈前剪枝
        if (a < 0 || a >= n || b < 0 || b >= m) {
            continue;
        }
        if (st[a][b]) {
            continue;
        }

        dfs(a, b, cnt + 1);
    }
    st[x][y] = false;  // 恢复现场
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int x, y;
        memset(st, 0, sizeof st);
        ans = 0;
        cin >> n >> m >> x >> y;

        dfs(x, y, 1);  // 参数3为已到达的点

        cout << ans << endl;
    }

    return 0;
}
