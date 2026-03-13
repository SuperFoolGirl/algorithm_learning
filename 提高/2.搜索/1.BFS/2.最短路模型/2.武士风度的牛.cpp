// 跳日字，给定终点和起点
// 本题需要统计步数，用dist取代st

#include <iostream>
#include <cstring>
#include <algorithm>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int N = 155;

int n, m;
char g[N][N];
PII q[N * N];
int dist[N][N];
// 8个日子
int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

int bfs(int sx, int sy) {
    int hh = 0, tt = 0;
    memset(dist, -1, sizeof dist);
    q[0] = {sx, sy};
    dist[sx][sy] = 0;

    while (hh <= tt) {
        PII t = q[hh++];

        for (int i = 0; i < 8; i++) {
            int a = t.x + dx[i], b = t.y + dy[i];
            if (a < 0 || a >= n || b < 0 || b >= m) {
                continue;
            }
            if (dist[a][b] != -1) {
                continue;
            }

            if (g[a][b] == 'H') {
                return dist[t.x][t.y] + 1;
            }
            q[++tt] = {a, b};
            dist[a][b] = dist[t.x][t.y] + 1;
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> m >> n;
    for (int i = 0; i < n; i++) {
        cin >> g[i];
    }

    int sx, sy;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == 'K') {
                sx = i, sy = j;
            }
        }
    }

    cout << bfs(sx, sy) << endl;

    return 0;
}
