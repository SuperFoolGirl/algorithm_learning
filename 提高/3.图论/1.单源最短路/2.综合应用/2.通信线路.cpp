// 与二分结合

// 本题实际在求路径上的第k+1长边
// 对于1~n的所有路径，求第k+1长的边的最小值(最大值最小)

// 什么问题可以用二分呢？
// 给定一个区间，要求一边是满足条件的，一边是不满足条件的，然后去找分界点
// 对于本题来说，边权为最大为1e6，但二分区间应为[0,1e6+1]，下面说明原因
// 设分界点为x，从1走到n的所有路中，最少经过y条长度大于x的边，且要求y<=k
// 若x大一些，则y就会更小一些，就会更加趋于满足条件
// 当y<k时，最佳答案一定<x；当找到分界点时，恰好有y=k，x为最小答案
// 因此，这是一个“最大值最小”问题，划分方式为[l,mid-1][mid,r]，满足条件的在右边
// 如果路线长度为k，那么答案可以取0，因此下界为0；
// 如果1~N不连通，那么答案最终会取到上界；1e6是可取范围，如果取到1e6，无法区分是答案还是无解，因此上界取1e6+1

// 求1~n最少经过几条长度大于x的边：
// 将所有边分类，若大于x边权为1，否则为0
// 因此，可以用双端队列出“1~n路线中最少经过几条长度大于x的边”
// 因此，代码结构就是最外层二分，枚举x，check部分是最短路，根据枚举的x，作上述工作：分类边、跑双端队列

#include <iostream>
#include <cstring>
#include <algorithm>
#include <deque>

using namespace std;

const int N = 1010, M = 20010;

int n, m, k;
int h[N], e[M], ne[M], w[M], idx;
int dist[N];
bool st[N];
deque<int> q;

void add(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

bool check(int x) {
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);
    dist[1] = 0;
    q.push_back(1);

    while (q.size()) {
        int t = q.front();
        q.pop_front();

        if (st[t]) {
            continue;
        }
        st[t] = true;

        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            // 处理边权
            int v = w[i] > x;
            if (dist[j] > dist[t] + v) {
                dist[j] = dist[t] + v;
                if (!v) {
                    q.push_front(j);
                } else {
                    q.push_back(j);
                }
            }
        }
    }

    return dist[n] <= k;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n >> m >> k;
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);
    }

    int l = 0, r = 1e6 + 1;
    while (l < r) {
        int mid = l + r >> 1;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    if (r == 1e6 + 1) {
        cout << -1 << endl;
    } else {
        cout << r << endl;
    }

    return 0;
}
