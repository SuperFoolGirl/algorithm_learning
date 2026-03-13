#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 2e5 + 10;

int n, k;
int q[N];
int dist[N];

int bfs() {
    int hh = 0, tt = 0;
    q[0] = n;
    memset(dist, -1, sizeof dist);
    dist[n] = 0;

    while (hh <= tt) {
        int t = q[hh++];

        // 这里的扩展方式比较特殊，直接枚举三种情况
        // 注意这种语法
        for (int a : {t - 1, t + 1, t * 2}) {
            if (a < 0 || a > N) {
                continue;
            }
            if (dist[a] != -1) {
                continue;
            }

            if (a == k) {
                return dist[t] + 1;
            }
            dist[a] = dist[t] + 1;
            q[++tt] = a;
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> k;
    cout << bfs() << endl;

    return 0;
}
