// 基于连通性的模型，BFS和DFS都能做
// 无向图，st数组

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110;

int n, k;
char g[N][N];
bool st[N][N];
int xa, ya, xb, yb;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

bool dfs(int x, int y) {
    // 起点特判(出栈后剪枝)
    if (g[x][y] == '#') {
        return false;
    }

    // 出口
    if (x == xb && y == yb) {
        return true;
    }

    // 扩展(本题无需恢复现场)

    // 标记
    st[x][y] = true;

    for (int i = 0; i < 4; i++) {
        int a = x + dx[i], b = y + dy[i];

        // 入栈前剪枝
        if (a < 0 || a >= n || b < 0 || b >= n) {
            continue;
        }
        // #判断在出栈后已经存在了，这里其实可以省略
        if (g[a][b] == '#' || st[a][b]) {
            continue;
        }

        // 注意，这里需要维护"返回值链"
        // 如果找到了正确答案，但此处不return，会自然执行到下面的return false
        // 递归问题，依旧是模拟递归树
        if (dfs(a, b)) {
            return true;
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> k;
    while (k--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> g[i];
        }
        memset(st, 0, sizeof st);

        cin >> xa >> ya >> xb >> yb;
        
        if (dfs(xa, ya)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
