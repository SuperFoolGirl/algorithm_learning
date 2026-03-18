// 最短路与DFS结合

// 根据题意
// 图联通
// 搜索一条路径，必须经过所有指定的点
// 点可重复走过

// 思路
// 一共需要拜访5个亲戚，即必须走过5个指定的点
// 这个要求，拆分来看就很简单了
// 1.枚举5!种拜访顺序，当然自己家0是第一位
// 2.以013425为例，求出0->1,1->3,3->4,4->2,2->5的最短路，累加起来就是013425的总路程
// 也就是，对于题设“必须经过所有点的最短路”，我们可以通过求多个两点之间最短路组合得到
// 基本思路就是dfs+spfa；虽然很适合floyd，但这题5w个点

// 即使是spfa也很吃力，需要考虑优化
// 如果是dfs+spfa，时间复杂度为5!*6*k*10^5，可能会超时
// 但对于一种排列，如果先spfa再dfs，即打表，就是6*k*10^5+5!了(每次spfa可以算出来一个点到其他所有点的最短路)
// 总的来说就是记忆化搜索/打表思想；其实如果还是按照dfs+spfa的话，记忆化搜索就完事了，无优化版本重复跑spfa了
// 不过既然能记忆化搜索，不如直接打表算了

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 50010, M = 200010, INF = 0x3f3f3f3f;

int n, m;
int source[6];
int h[N], e[M], ne[M], w[M], idx;
int q[N], dist[6][N];
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

// 局部变量和全局变量可以重名，优先使用局部变量名
void spfa(int start, int dist[]) {
    // 参数3不可写sizeof dist，有歧义
    // 这里写字节数，N个int
    memset(dist, 0x3f, N * 4);
    dist[start] = 0;
    int hh = 0, tt = 1;
    q[0] = start;
    st[start] = true;

    while (hh != tt) {
        int t = q[hh++];
        if (hh == N) {
            hh = 0;
        }
        st[t] = false;

        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                if (!st[j]) {
                    q[tt++] = j;
                    if (tt == N) {
                        tt = 0;
                    }
                    st[j] = true;
                }
            }
        }
    }
}

// u: 当前拜访的亲戚
// start: 并不是剪枝，而是“边”的起点的下标
// distance: 当前累计距离
int dfs(int u, int start, int distance) {
    if (u == 6) {
        return distance;
    }

    // 指数型枚举
    // 本题与顺序有关，不是组合问题，而是排列问题
    // 因此只需要用st限制已选，不需要优化冗余(扩展出去的dfs，扩展时仍从1开始枚举)
    int res = INF;
    for (int i = 1; i <= 5; i++) {
        if (st[i]) {
            continue;
        }
        int next = source[i];
        st[i] = true;
        res = min(res, dfs(u + 1, i, distance + dist[start][next]));
        st[i] = false;
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n >> m;
    source[0] = 1;  // 自己家
    for (int i = 1; i <= 5; i++) {
        cin >> source[i];
    }

    memset(h, -1, sizeof h);
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);
    }

    // 打表spfa
    for (int i = 0; i < 6; i++) {
        // dist[i][j]表示i->j的最短路
        spfa(source[i], dist[i]);
    }

    // 暴搜
    cout << dfs(1, 0, 0) << endl;

    return 0;
}
