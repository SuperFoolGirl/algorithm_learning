#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 40010, M = N * 2;

int n, m;
int h[N], e[M], ne[M], idx;
int fa[N][16], depth[N];
int q[N];

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

void bfs(int root) {
    // 深度初始化
    memset(depth, 0x3f, sizeof depth);
    // 哨兵深度为0，根结点深度为1
    depth[0] = 0, depth[root] = 1;

    int hh = 0, tt = 0;
    q[0] = root;
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            
            // 这是无向图，需要判断是否访问过，防止死循环
            if (depth[j] > depth[t] + 1) {
                depth[j] = depth[t] + 1;
                q[++tt] = j;

                // 初始化fa数组
                // 按两个分段来写
                fa[j][0] = t;
                for (int k = 1; k <= 15; k++) {
                    fa[j][k] = fa[fa[j][k - 1]][k - 1];
                }
            }
        }
    }
}

int lca(int a, int b) {
    // 预处理：让a在b的下面，统一处理，避免代码冗余
    if (depth[a] < depth[b]) {
        swap(a, b);
    }

    // 1.先跳到同一层，拼出二进制
    for (int k = 15; k >= 0; k--) {
        // 如果a跳了2^k步之后，仍然在b的下面或同一层，就可以跳
        // 如果跳出根结点，得到哨兵depth=0，不会满足此处条件(根结点为1)，说明b不在此树上
        if (depth[fa[a][k]] >= depth[b]) {
            a = fa[a][k];
        }
    }
    // 若果a和b已经相等了，说明b是a的祖先，直接返回即可
    if (a == b) {
        return a;
    }

    // 2.同时跳，直到a和b跳到lca的下一层
    for (int k = 15; k >= 0; k--) {
        if (fa[a][k] != fa[b][k]) {
            a = fa[a][k];
            b = fa[b][k];
        }
    }

    // 最后，往上跳一步就到了
    return fa[a][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    int root;
    memset(h, -1, sizeof h);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        if (b == -1) {
            root = a;
        } else {
            add(a, b);
            add(b, a);
        }
    }

    // 从root出发，预处理depth和fa数组
    // 宽搜深搜都可以，为了防止爆栈，这里用宽搜
    bfs(root);

    // 处理查询
    cin >> m;
    while (m--) {
        int a, b;
        cin >> a >> b;

        int p = lca(a, b);

        if (p == a) {
            cout << '1' << endl;
        } else if (p == b) {
            cout << '2' << endl;
        } else {
            cout << '0' << endl;
        }
    }

    return 0;
}
