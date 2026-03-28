// 第一问，在图中求最少要多少个点，从它们出发能到达图中所有点(不含彼此)
// 第二问，最少需要加几条边，才能使图变成SCC

// 本题数据范围较小，也可以用floyd求传递闭包

// 那么，如何考虑SCC做法呢？
// 这里给出一种通用的思考方式
// 首先，求出SCC并缩点后，会得到DAG
// 设DAG有p个起点(入度为0)和q个终点(出度为0)
// 从p和q入手，结合题设进行分析

// 以本题为例：
// 第一问，答案就是p。因为起点之间互相不可达，因此必须从每个起点出发才能覆盖所有点
// 第二问，如果要想把整个图变成SCC，那缩点后只有一个，则p=q=1
// 对于此刻现状——p个起点和q个终点，我们要加一定数量的边，使当前DAG变成SCC，再缩点后只有一个点
// 结论：需要加的边数至少是max(p, q)，p!=1且q!=1

// 下面证明max(p, q)这个答案的可行性：
// 不妨设p<=q，往证答案是q
// 特判：若p=q=1，则不需要加边
// ① p=1, 即起点唯一，那么p可以走到所有的终点；这种情况，对每个终点连一条指向起点的边，则可行
// ② p>1，则p和q至少为2；设存在p1->...->q1, p2->...->q2的路径，下面证明一定能挑选出来这两组点，使得p1!=p2且q1!=q2
//   反证：如果不存在这样的两组点，则所有起点都只能走到同一个终点；这与假设条件q>=p>1矛盾
//   继续。从q1连一条边到p2，此时形成了一条链: p1->...->q1->p2->...->q2，此时将p2移出起点集合，q1移出终点集合；
//   因此，p1->...->q2视为新的一组点，再找一组，执行上述相同的工作
//   直到p只剩下一个，此时转为情况①
//   统计总共加边条数：(p-1)+(q-(p-1))=q

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

// 没有给边的范围，但最多为N^2级别(双向完全图)
const int N = 110, M = 10010;

int n;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];
int id[N], scc_cnt;
int din[N], dout[N];

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u;
    in_stk[u] = true;

    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        } else if (in_stk[j]) {
            low[u] = min(low[u], dfn[j]);
        }
    }

    if (low[u] == dfn[u]) {
        int y;
        scc_cnt++;
        do {
            y = stk[top--];
            in_stk[y] = false;
            id[y] = scc_cnt;
        } while (y != u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i++) {
        // 输入所有出边指向的点
        int t;
        while (cin >> t, t) {
            add(i, t);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    // 统计DAG中每个点的入度和出度
    for (int u = 1; u <= n; u++) {
        for (int i = h[u]; ~i; i = ne[i]) {
            int j = e[i];
            if (id[u] != id[j]) {
                din[id[j]]++;
                dout[id[u]]++;
            }
        }
    }

    int p = 0, q = 0;
    for (int i = 1; i <= scc_cnt; i++) {
        if (!din[i]) {
            p++;
        }
        if (!dout[i]) {
            q++;
        }
    }

    // 问题1
    cout << p << endl;

    // 问题2
    if (scc_cnt == 1) {
        cout << 0 << endl;
    } else {
        cout << max(p, q) << endl;
    }

    return 0;
}
