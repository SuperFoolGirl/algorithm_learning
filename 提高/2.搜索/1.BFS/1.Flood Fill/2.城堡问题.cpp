// 处理二进制编码
// 最高效的方法是直接位运算

#include <iostream>
#include <cstring>
#include <algorithm>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int N = 55;

int n, m;
int g[N][N];
PII q[N * N];
bool st[N][N];
// 二进制权重：南-东-北-西
// 左移&1是从低位到高位的，因此反向存储
int dx[4] = {0, -1, 0, 1};
int dy[4] = {-1, 0, 1, 0};

int bfs(int sx, int sy) {
    int hh = 0, tt = 0;
    int area = 0;

    q[0] = {sx, sy};
    st[sx][sy] = true;

    while (hh <= tt) {
        auto t = q[hh++];
        area++;  // 无边权，出入队统计皆可

        for (int i = 0; i < 4; i++) {
            int a = t.x + dx[i], b = t.y + dy[i];
            if (a < 0 || a >= n || b < 0 || b >= m) {
                continue;
            }
            if (st[a][b]) {
                continue;
            }
            // 判断是否有墙
            if (g[t.x][t.y] >> i & 1) {
                continue;
            }

            q[++tt] = {a, b};
            st[a][b] = true;
        }
    }

    return area;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // 输入每一个坐标墙的情况
            // bfs时，根据墙的情况，选择可走路径
            cin >> g[i][j];
        }
    }

    int cnt = 0, area = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!st[i][j]) {
                area = max(area, bfs(i, j));
                cnt++;
            }
        }
    }

    cout << cnt << endl << area << endl;

    return 0;
}
