// 如果不用SCC，需要判断目标点是否能被所有点走到；可以反向思考，从目标点出发，看看能否走到其他所有点即可。
// 时间复杂度为平方

// 用SCC解决的话，转为DAG。在DAG上，如果存在至少两个终点(出度为0)，则一定无解：终点无出边，两终点直接必然无沟通，一定不满足题意；
// 如果只有一个终点，那么答案为“1”，只有终点能够作为答案：一个图中可能存在多个拓扑序，但在终点唯一的情况下，在所有排列中，终点都在最后的位置
// 注意，终点是缩点后的点，其作为SCC包含几个原图的点不一定是1；因此需要输出构成该SCC的点数
// 时间复杂度为线性

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 10010, M = 50010;

int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;

// 这里对静态栈、队列进行下书写习惯的补充
// 只有循环队列，队尾tt指向最后元素的下一个位置，入队时q[tt++]；初始化hh=0, tt=1
// 普通队列、栈，队尾tt和栈顶top都指向最后一个元素本身，入队/入栈时q[++tt]/stk[++top]；初始化hh=0,
// 若tt/top=0，则第一次入队/入栈时写q[0]/stk[0]；若tt/top=-1，则第一次入队可以统一形式q[++tt]
// 我个人习惯喜好第一种
// 特别地，栈只有一个指针，含有自减操作。++top和top--是一对操作，前置后置要错开
int stk[N], top;
bool in_stk[N];

// SCC套装。sz数组用于统计每个SCC包含的点数
int id[N], scc_cnt, sz[N];
int dout[N];  // 记录由SCC构成的DAG中每个点的出度

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
        scc_cnt++;
        int y;
        do {
            y = stk[top--];
            in_stk[y] = false;
            id[y] = scc_cnt;
            sz[scc_cnt]++;
        } while (y != u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m--) {
        int a, b;
        cin >> a >> b;
        add(a, b);
    }

    // 注意原图不一定连通，因此需要对每个点都进行一次Tarjan
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    // 统计新图中点的出度——遍历所有边
    for (int u = 1; u <= n; u++) {
        for (int i = h[u]; ~i; i = ne[i]) {
            int j = e[i];
            // id[u]为u所属SCC的编号，也就是新图中点的编号
            if (id[u] != id[j]) {
                dout[id[u]]++;
            }
        }
    }

    // 统计出度为0(终点)点的个数及其包含原图点的个数
    int zeros = 0, sum = 0;
    for (int i = 1; i <= scc_cnt; i++) {
        if (!dout[i]) {
            zeros++;
            sum += sz[i];
        }

        // 根据题意，只有一个终点才有解
        if (zeros > 1) {
            sum = 0;
            break;
        }
    }

    cout << sum << endl;

    return 0;
}
