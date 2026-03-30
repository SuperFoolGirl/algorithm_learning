// 难点在于如何抽象出图论模型
// 下面分析样例

// 共9个站点，3趟车次
// 对于每车次，首为起点，末为终点
// 对于车次1：1->3->5->6，中间经过了2,4却没有停靠
// 说明2,4等级严格小于1,3,5,6
// 对于等级b<a，连一条a->b的边
// 因此，2,4分别向1,3,5,6连边

// 有感觉了，差分约束
// 边权就是等级
// 保证得到的权值最小，那么令图中只有两种边权：0,1
// 0表示等级相等，1表示等级严格小于
// 本题保证有解，那么建图后一定是DAG
// 本题要求最小值，因此还是最长路

// 但是问题在于，数据量太大，会MLE
// 因此，要在建图时优化
// 通过上述讲解，本题建图规模是n^2级别：给定两个点集，点集1(n个点)向点集2(m个点)连边，边数为n*m
// 此时，在两个点集间设立虚拟点，点集1向虚拟点连边，边权为0，虚拟点向点集2连边，边权为1；边数为n+m，规模大大降低
// 但是必须保证，点集1中的每个点，都需要向点集2中的每个点连边，保证边数严格为n*m；否则，这个虚拟点在意义上就无法成立
// 这样，不管是建图的空间消耗，还是遍历的时间消耗，都大大降低了

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 2010, M = 1000010;

int n, m;
int h[N], e[M], ne[M], w[N], idx;
int q[N], d[N];
int dist[N];
bool st[N];  // 记录每车次中停靠的站点

void add(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
    d[b]++;  // 涉及拓扑排序的建图可以统一在add里统计入度
}

void toposort() {
    int hh = 0, tt = -1;
    // 加了m个虚拟点，编号为n+1~n+m
    for (int i = 1; i <= n + m; i++) {
        if (!d[i]) {
            q[++tt] = i;
        }
    }

    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (--d[j] == 0) {
                q[++tt] = j;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    memset(h, -1, sizeof h);

    for (int i = 1; i <= m; i++) {
        memset(st, 0, sizeof st);
        int cnt;
        cin >> cnt;
        // 根据题意，start是起始站，end是终点
        // 不过其实并不依赖这一条件。因此我们让start统计最小的站点编号，end统计最大的站点编号
        // 目的是为了锁定选中停靠站的范围，避免多余枚举
        int start = n, end = 1;
        while (cnt--) {
            int stop;
            cin >> stop;
            start = min(start, stop);
            end = max(end, stop);
            st[stop] = true;
        }

        int ver = n + i;  // 虚拟点编号，必须保证不与原图点重叠
        for (int j = start; j <= end; j++) {
            // !st[j]∈点集1，st[j]∈点集2
            if (!st[j]) {
                add(j, ver, 0);
            } else {
                add(ver, j, 1);
            }
        }
    }

    // 保证是DAG，但是要取拓扑序
    toposort();

    // 每个点的等级至少是1，因此dist要初始化为1(像第三题一样，也可以虚拟源点扩散)
    for (int i = 1; i <= n + m; i++) {
        dist[i] = 1;
    }

    // 本题递推顺序是正拓扑序
    for (int u = 0; u < n + m; u++) {
        int t = q[u];
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            dist[j] = max(dist[j], dist[t] + w[i]);
        }
    }

    // 统计答案时可别算上虚拟点
    int res = 0;
    for (int i = 1; i <= n; i++) {
        res = max(res, dist[i]);
    }
    cout << res << endl;

    return 0;
}
