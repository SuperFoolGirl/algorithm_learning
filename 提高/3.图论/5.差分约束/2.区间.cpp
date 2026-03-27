// ci<=区间长度，因此一定有解：最坏的情况下可以取遍区间所有整数值
// 区间范围是[0,50000]，手动将其平移至[1,50001]，以为前缀和(也就是超级源点)服务

// 找不等式关系：
// 把所有输入的ai记为ai+1，bi记为bi+1，便于求前缀和
// si表示1-i中被选出的树的个数，则s50001的最小值就是答案
// 求最小值，进而就有>=不等式->最求大下界->求最长路
// 整理条件：
// ① si>=si-1, 1<=i<=50001；可以构造出0->1->2->...->i的路径，即0号点可以遍历到所有点，进而能遍历到所有边 => 找到超级源点了
// ② si-(si-1)<=1, 这个式子表示i有没有被选，只能是0或1，变形为：(si-1)>=si-1，构造出>=不等式
// ③ sb-(sa-1)>=c => [a,b]中至少选c个，变形为：sb>=sa-1+c
// 已经挖掘出了所有条件+超级源点，结束

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 50010, M = 150010;  // 三种情况，每种5w边

int n;
int h[N], e[M], ne[M], w[M], idx;
int dist[N];
int q[N];  // 一定有解，不必再判正环
bool st[N];

void add(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

void spfa() {
    int hh = 0, tt = 1;
    memset(dist, -0x3f, sizeof dist);
    dist[0] = 0;
    q[0] = 0;
    st[0] = true;

    while (hh != tt) {
        int t = q[hh++];
        if (hh == N) {
            hh = 0;
        }
        st[t] = false;

        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (dist[j] < dist[t] + w[i]) {
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    memset(h, -1, sizeof h);

    // 1.从i-1到i的边，权重为0
    // 2.从i到i-1的边，权重为-1
    for (int i = 1; i <= 50001; i++) {
        add(i - 1, i, 0);
        add(i, i - 1, -1);
    }
    // 3.对于输入的区间，建立边
    while (n--) {
        int a, b, c;
        cin >> a >> b >> c;
        a++, b++;  // 平移
        add(a - 1, b, c);
    }

    spfa();

    cout << dist[50001] << endl;

    return 0;
}
