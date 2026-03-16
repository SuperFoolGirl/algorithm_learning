// 这题第一思路应该是搜索，不过数据范围太大了
// 依然是将每个站点看成点，但是要根据题目给出的路线来建图
// 如路线是3->1->2，那么就有边3->1，1->2，3->2

// 为什么要统计3->2呢？它可以由两外两条路组合而来
// 因为本题要统计换乘次数，即坐车次数-1，即路径边数-1
// 我们需要得到边数最少的路，而非边权最小的路
// 因此这是一个BFS问题

#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>

using namespace std;

const int N = 510;

// 本题边数不定，因此用邻接矩阵
int n, m;
bool g[N][N];
int dist[N];
int stop[N];  // 统计每条线路的站点情况
int q[N];

void bfs() {
    int hh = 0, tt = 0;
    memset(dist, -1, sizeof dist);
    q[0] = 1;
    dist[1] = 0;

    while (hh <= tt) {
        int t = q[hh++];
        for (int i = 1; i <= n; i++) {
            if (!g[t][i]) {
                continue;
            }
            if (dist[i] != -1) {
                continue;
            }

            dist[i] = dist[t] + 1;
            q[++tt] = i;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> m >> n;
    string line;
    getline(cin, line);    // 读掉第一行末尾的换行符
    while (m--) {
        // 不知道每条路线有多少个站点，因此用getline读整行，再用stringstream来分割
        // stringstream相当于sscanf，但更强更方便
        // stringstream可以把line中由空白字符分隔的内容依次读出来，直到读完为止
        getline(cin, line);
        stringstream ssin(line);
        int cnt = 0, p;
        while (ssin >> p) {
            stop[cnt++] = p;
        }
        // 建边：若该路线有n个站点，则有Cn2条边
        for (int i = 0; i < cnt; i++) {
            for (int j = i + 1; j < cnt; j++) {
                g[stop[i]][stop[j]] = true;
            }
        }
    }

    bfs();

    if (dist[n] == -1) {
        cout << "NO" << endl;
    } else {
        cout << dist[n] - 1 << endl;    // 换乘次数=坐车次数-1=路径边数-1
    }
    // 特判：起点与终点相同，为0
    cout << max(dist[n] - 1, 0) << endl;

    return 0;
}
