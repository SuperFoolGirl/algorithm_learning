// 与《没有上司的舞会》有关系
// 那道题是，每条边上，至多选一个点，求树的最大独立集的大小
// 本题，每条边上，最少选择一个点，求最小权值

// 树形DP+状态机
// 其实《舞会》那道题也是用了状态机的
// 状态表示 f(i,j) j=0,1
// 集合：所有以i为根的子树，且点i状态为j的所有选法
// j=0：点i不选，j=1：点i选
// 属性：min
// 状态计算
// 点i不选时，其所有儿子必须选
// f(i,0) = sum{f(son,1)}
// 点i选时，其所有儿子可以选也可以不选
// f(i,1) = sum{min{f(son,1),f(son,0)}}+1
// +1在代码里放到初始化里，因为要考虑叶子结点无法DP的问题

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1510;

int n;
int h[N], e[N], ne[N], idx;
int f[N][2];
bool st[N];  // 寻找根结点

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

void dfs(int u) {
    // 根据题意初始化：如果选了u，那f[u][1]至少为1(不考虑下儿子们)
    // 对于叶子来说，叶子也没有儿子，选了叶子，那f[u][1]就是1
    // 因为叶子进不去for循环，因此树形DP必须先考虑叶子的初始化
    f[u][1] = 1;
    f[u][0] = 0;

    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        dfs(j);

        f[u][0] += f[j][1];
        f[u][1] += min(f[j][0], f[j][1]);
    }
}

int main() {
    // scanf会返回成功读取的输入个数，这里只输入一个%d，因此返回1表示成功读取了一个整数
    while (scanf("%d", &n) == 1) {
        memset(h, -1, sizeof h);
        idx = 0;
        memset(st, false, sizeof st);

        for (int i = 0; i < n; i++) {
            int id, cnt;
            scanf("%d:(%d)", &id, &cnt);
            while (cnt--) {
                int son;
                scanf("%d", &son);
                add(id, son);
                st[son] = true;  // 有父结点
            }
        }

        // 寻找根结点
        int root = 0;
        while (st[root]) {
            root++;
        }

        // 树形DP无法迭代，只能递归
        dfs(root);

        printf("%d\n", min(f[root][0], f[root][1]));
    }

    return 0;
}
