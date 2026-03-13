// 将A矩阵中所有的1作为多源起点往外扩散即可，步数记录在B中
// 根据定义，A中的1全部变为B中的0

// 图论中，如果要求所有点到一系列起点的距离，进而找到最近起点
// 可以转为单源最短路：给这些起点添加一个虚拟源点，向这些起点连边，边权为0
// 这里只是提一句，本题多源BFS用不到，直接入队所有起点即可

#include <iostream>
#include <cstring>
#include <algorithm>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int N = 1010;

int n, m;
char g[N][N];
PII q[N * N];
int dist[N][N];
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

void bfs() {
    // 多源BFS不止入队q[0]，因此tt初始化-1，持续++tt入队
    int hh = 0, tt = -1;
    memset(dist, -1, sizeof dist);
    
    // 将所有起点入队
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == '1') {
                q[++tt] = {i, j};
                dist[i][j] = 0;
            }
        }
    }

    while (hh <= tt) {
        PII t = q[hh++];

        for (int i = 0; i < 4; i++) {
            int a = t.x + dx[i], b = t.y + dy[i];
            if (a < 0 || a >= n || b < 0 || b >= m) {
                continue;
            }
            if (dist[a][b] != -1) {
                continue;
            }

            q[++tt] = {a, b};
            dist[a][b] = dist[t.x][t.y] + 1;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> g[i];
    }

    bfs();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << dist[i][j] << ' ';
        }
        cout << endl;
    }

    return 0;
}
