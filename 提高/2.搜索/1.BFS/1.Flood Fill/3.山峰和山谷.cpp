// 连通块的判定问题
// 对于每次扩展，如果遇到非连通块区域，此时应当进行一次判断
// 在求连通块的过程中，可以遍历到其所有边界
// 而对于山峰/山谷的判定，需要以所有边界(每一格)的情况为依据
// 如果边界上没有低于连通块的，那连通块才是山峰；如果边界上没有高于连通块的，那连通块才是山谷

#include <iostream>
#include <cstring>
#include <algorithm>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int N = 1010;

int n, m;
int g[N][N];
PII q[N * N];
bool st[N][N];

void bfs(int sx, int sy, bool& has_higher, bool& has_lower) {
    int hh = 0, tt = 0;
    q[0] = {sx, sy};
    st[sx][sy] = true;

    while (hh <= tt) {
        auto t = q[hh++];

        // 八联通
        for (int i = t.x - 1; i <= t.x + 1; i++) {
            for (int j = t.y - 1; j <= t.y + 1; j++) {
                if (i == t.x && j == t.y) {
                    continue;
                }
                if (i < 0 || i >= n || j < 0 || j >= m) {
                    continue;
                }
                if (st[i][j]) {
                    continue;
                }
                if (g[i][j] != g[t.x][t.y]) {
                    // 到达连通块边缘，开始统计
                    if (g[i][j] > g[t.x][t.y]) {
                        has_higher = true;
                    } else {
                        has_lower = true;
                    }
                }

                q[++tt] = {i, j};
                st[i][j] = true;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> g[i][j];
        }
    }

    int peak = 0, valley = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!st[i][j]) {
                bool has_higher = false, has_lower = false;
                bfs(i, j, has_higher, has_lower);
                if (!has_higher) {
                    peak++;
                }
                if (!has_lower) {
                    valley++;
                }
            }
        }
    }

    cout << peak << " " << valley << endl;

    return 0;
}
