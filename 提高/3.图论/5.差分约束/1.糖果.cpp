// 不等式组要求统一用>=或<=，本题为求最小值，因此用>=，求最长路
// 求出每个点的最小值，求和后就是和的最小值，也就是本题答案
// 对于A=B的情况，如何只用>=表示？很简单：A>=B, B>=A
// 那对于A<B呢？B>=A+1
// 总之，要统一用>=去表示=, <, >, <=

// 每个小朋友都要分到糖果->x>=1
// 设置超级源点x0=0，则建立所有x>=x0+1

// 考虑边数上限
// 最坏情况下，都是A=B，建两条边
// 超级源点又要对每个点建边
// 因此最大边数为3M

#include <algorithm>
#include <cstring>
#include <iostream>


using namespace std;

typedef long long LL;

const int N = 100010, M = 300010;

int n, m;
int h[N], e[M], w[M], ne[M], idx;
int dist[N];
int q[N], cnt[N];
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

// 注意，本题spfa的主任务是求最长路，因此不能只找负环
// dist必须初始化为-INF了，不得不牺牲一些求负环的效率
// 另外，本题求负环TLE了，因此把队列换成栈
// 操作：1.出栈为q[--tt]，这两个情况下tt都指向尾元素的下一个 2.去掉队列的循环
bool spfa() {
    int hh = 0, tt = 1;
    memset(dist, -0x3f, sizeof dist);

    dist[0] = 0;    // 超级源点入队
    q[0] = 0;
    st[0] = true;

    while (hh != tt) {
        int t = q[--tt];
        st[t] = false;

        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] < dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                cnt[j] = cnt[i] + 1;

                // 注意，加上源点，有n+1个点
                if (cnt[j] >= n + 1) {
                    return false;
                }

                if (!st[j]) {
                    q[tt++] = j;
                    st[j] = true;
                }
            }
        }
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m--) {
        int x, a, b;
        cin >> x >> a >> b;
        if (x == 1) {
            add(a, b, 0);
            add(b, a, 0);
        } else if (x == 2) {
            add(a, b, 1);
        } else if (x == 3) {
            add(b, a, 0);
        } else if (x == 4) {
            add(b, a, 1);
        } else {
            add(a, b, 0);
        }
    }

    // 建立超级源点0
    for (int i = 1; i <= n; i++) {
        add(0, i, 1);
    }

    // 负环说明无解
    if (!spfa()) {
        cout << -1 << endl;
    } else {
        LL res = 0;
        for (int i = 1; i <= n; i++) {
            res += dist[i];
        }
        cout << res << endl;
    }

    return 0;
}
