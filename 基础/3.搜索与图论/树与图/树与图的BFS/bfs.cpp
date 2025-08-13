// 对于树来说，树的广度优先搜索，其实就是层序遍历

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10, M = 2 * N;
int n, m;

// 索引 idx 代表的是用户输入边时的顺序，即 idx 是边的编号，与点无关
// h[i] 存储的是以节点 i 为起点的第一条边在 e 和 ne 数组中的索引idx
// e[idx] 存储的是索引为 idx 的这条边所指向的目标节点，即出边指向的点
// ne[idx] 存储的是与索引为 idx 的这条边同起点的下一条边在 e 和 ne 数组中的索引idx。也就是儿子们串起来了
// 所以，e[h[a]] 就可以访问到 a 的第一条出边所指向的结点

// 总结，idx是边的编号，h[点]存储idx来表示第一条出边，e[边]存储边指向的点，ne[边]存储该边同起点的下一条边
int h[N], e[M], ne[M], idx;

int q[N], d[N];

void add(int a, int b) {
    e[idx] = b;    // 新开一个点
    ne[idx] = h[a];
    h[a] = idx++;
}

int bfs() {
    int hh = 0, tt = 0;
    q[0] = 1;    // 根节点从1开始，idx从0开始。队列存的是结点

    memset(d, -1, sizeof d);
    d[1] = 0;

    while (hh <= tt) {
        int t = q[hh++];

        // 遍历所有的儿子
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];    // j存储出边指向的点

            if (d[j] != -1) {
                continue;
            }

            d[j] = d[t] + 1;
            q[++tt] = j;
        }
    }

    return d[n];
}

int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);

    // 点的编号从1开始
    // 输入时，最小值为1
    // 而idx是插入点的顺序，与点的编号无关
    // 1号点是根节点
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
    }

    // 输出到最后一个节点n的最短路
    cout << bfs() << endl;
    return 0;
}
