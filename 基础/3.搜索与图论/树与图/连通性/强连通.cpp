// 对于有向图G(V,E)，其强连通分量是图G的一个极大子图G'(V',E')，其中对于任意u，v属于V'，都存在从u到v的路径且存在从v到u的路径。
// 如果要判断G本身是否为强连通图，只需说明任意两个节点u，v之间都存在路径即可。

// 这里讲Tarjan算法，时间复杂度O(V+E)
// 其核心思想是在 DFS 过程中，通过维护两个关键的时间戳/追溯值 (dfn 和
// low)，来实时判断节点是否属于同一个SCC，并利用一个栈 (stk) 来暂存待确认的节点。

#include <algorithm>
#include <cstring>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// 最大节点数和最大边数
const int N = 1e5 + 10, M = 2 * N;

int h[N], e[M], ne[M], idx;

// 添加一条从 a 到 b 的有向边
void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

int n, m;
int dfn[N], low[N];    // dfn: 时间戳，记录节点u第一次被访问的时间；low: 追溯值记录节点u及其子树中的所有节点，通过至多一条回边能到达的dfn值最小的节点。
int timer;             // 时间戳计数器
stack<int> stk;        // 辅助栈，存储正在搜索中的节点
bool in_stk[N];        // 标记节点是否在栈中
int scc_cnt;           // 强连通分量 (SCC) 的数量
int belong[N];         // belong[i]: 节点 i 所属的 SCC 编号

void tarjan(int u) {
    // 1. 设置时间戳和追溯值，并将节点入栈
    dfn[u] = low[u] = ++timer;
    stk.push(u);
    in_stk[u] = true;

    // 2. 遍历所有出边
    for (int i = h[u]; i != -1; i = ne[i]) {
        int v = e[i];

        // 情况 A: 邻接点 v 未被访问，进行递归
        if (!dfn[v]) {
            tarjan(v);
            // 递归返回后，用子节点v的low值更新u的low值
            // 这意味着u节点的最低追溯点不仅可以通过u自己找到的回边，还可以通过它的子树中的节点找到的回边来确定。
            low[u] = min(low[u], low[v]);
        }
        // 情况 B: 邻接点v已被访问，且v仍在栈中，说明u，v属于一个环
        else if (in_stk[v]) {
            // 用 v 的 dfn 值更新 u 的 low 值 (不能用 low[v])
            low[u] = min(low[u], dfn[v]);
        }
        // 情况 C: 邻接点 v 已被访问但不在栈中，v 所属的 SCC 已确定，忽略此边。
    }

    // 3. 判定 SCC 的根
    if (dfn[u] == low[u]) {
        // 发现一个 SCC，u 是该 SCC 的根
        scc_cnt++;
        int v;
        // 不断从栈中弹出节点，直到弹出 u 为止，这些节点构成一个 SCC
        do {
            v = stk.top();
            stk.pop();
            in_stk[v] = false;
            belong[v] = scc_cnt;    // 标记 v 所属的 SCC 编号
        } while (u != v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;

    memset(h, -1, sizeof h);    // 初始化邻接表头指针

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
    }

    // 对每个未访问的节点，调用 tarjan 进行搜索
    // 确保处理到所有不连通的子图
    // 其实这里就是连通块的处理方式
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    cout << "强连通分量的总数: " << scc_cnt << endl;
    cout << "每个节点所属的 SCC 编号 (节点: 编号):" << endl;
    for (int i = 1; i <= n; i++) {
        cout << i << ": " << belong[i] << endl;
    }

    return 0;
}
