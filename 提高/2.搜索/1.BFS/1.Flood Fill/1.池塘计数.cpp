#include <iostream>
#include <cstring>
#include <algorithm>

#define x first
#define y second

using namespace std;

typedef pair<int, int> PII;

const int N = 1010, M = N * N;

int n, m;
bool st[N][N];
char g[N][N];
PII q[M];

void bfs(int sx, int sy) {
    // 起点入队+起点标记
    // tt初始化0或-1皆可，-1的话q[0]写作q[++tt]
    // 这里为了方便，用hh和tt都记为0的方式
    // 出队时hh++，取队首同时指针向后；入队时++tt，先指针向后再入队
    int hh = 0, tt = 0;
    q[0] = {sx, sy};
    st[sx][sy] = true;

    // 可以发现模拟队列代码更简洁一些
    while (hh <= tt) {
        PII t = q[hh++];

        // 八个方向，这里不用方向数组，两重循环挖去中间
        for (int i = t.x - 1; i <= t.x + 1; i++) {
            for (int j = t.y - 1; j <= t.y + 1; j++) {
                if (i == t.x && j == t.y) {
                    continue;
                }
                if (i < 0 || i >= n || j < 0 || j >= n) {
                    continue;
                }
                if (g[i][j] == '.' || st[i][j]) {
                    continue;
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
    // 二维字符数组可以直接输入一行
    for (int i = 0; i < n; i++) {
        cin >> g[i];
    }

    int cnt = 0;
    for (int i = 0 ; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (g[i][j] == 'W' && !st[i][j]) {
                bfs(i, j);
                cnt++;
            }
        }
    }

    cout << cnt << endl;

    return 0;
}
