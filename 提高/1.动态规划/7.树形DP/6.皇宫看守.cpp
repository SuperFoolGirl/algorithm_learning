// 与第5题、舞会是一类问题
// 本题要求，以路径u-v-w为例
// 在u、v、w任意放一个警卫，都能保证v满足条件：
// 在u上放：v被父结点的警卫看守覆盖
// 在w上放：v被儿子结点的警卫看守覆盖
// 在v上放：v被自己的警卫看守覆盖
// 要求全局的点都被该规则覆盖，且放置的警卫数量最少
// 注意，一个点可以同时被多个警卫覆盖，虽然我们要求最少，但这个情况可能无法避免

// 多了一重状态，下面列写状态机
// f(i,0): 点i被父结点的警卫看守覆盖
// f(i,1): 点i被子结点的警卫看守覆盖
// f(i,2): 点i被自己的警卫看守覆盖

// 注意，树一般情况下不要向上考虑
// 即在列写状态转移方程时，应该是“由子结点的状态转移而来”，不能同时由祖宗转移而来

// 1. f[i][0]=sum{min{f[son][1],f[son][2]}}
// i的父亲放了，i没放，i的儿子就不能倚仗i了

// 2. f[i][1]
// i的儿子放了，但是几个儿子都可以，只需要保证至少有一个儿子放了就行。
// 枚举儿子k放置守卫：f[k][2]，其他儿子可放可不放：sum{min{f[son][1],f[son][2]}}
// f[i][1]=min{f[k][2]+sum{min{f[son][1],f[son][2]}}},son为除了k以外的儿子
// 注意，其他儿子的方程形式同f[i][0]，代码上可以借此简化

// 3. f[i][2]=sum{min{f[son][0],f[son][1],f[son][2]}}+w[i]
// i自己放了，那i的儿子三种情况随意

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1510;

int n;
int h[N], e[N], ne[N], w[N], idx;
int f[N][3];
bool st[N];  // 题目没说1是根，需要自己找

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

void dfs(int u) {
    f[u][2] = w[u];

    // 观察f[u][1]的表达式，与f[u][0]的表达式很接近，可以换用更清爽的写法
    // 另外注意，f[u][1]的每次更新，都需要把所有儿子算出来才行
    // 不像其他的表达式，对所有儿子一起取最值，因此可以在遍历儿子时不断更新打擂台
    // f[u][1]每次更新都需要处理儿子的和，而不是简单的儿子打擂台
    // ~i是按位取反，等价于-i-1
    // 而在模拟邻接表中，恰好以i=-1作为结束标志，因此~i为0，表达式为假，循环结束
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        dfs(j);

        f[u][0] += min(f[j][1], f[j][2]);
        f[u][2] += min(f[j][0], f[j][1], f[j][2]);
    }

    // 计算完所有儿子，更新f[u][1]
    // 不像那两个，最外层是sum计数，初始化默认0即可
    // f[u][1]最外层是min，需要min初始化
    f[u][1] = 1e9;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        f[u][1] = min(f[u][1], f[j][2] + f[u][0] - min(f[j][1], f[j][2]));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;

    memset(h, -1, sizeof h);

    for (int i = 0; i < n; i++) {
        int id, cost, cnt;
        cin >> id >> cost >> cnt;
        w[id] = cost;  // 本题为点权，不是边权
        while (cnt--) {
            int son;
            cin >> son;
            add(id, son);
            st[son] = true;
        }
    }

    int root = 1;  // 本题序号从1开始
    while (st[root]) {
        root++;
    }

    dfs(root);

    cout << min(f[root][1], f[root][2]) << endl;  // 根结点没有父结点，因此不能被父结点覆盖

    return 0;
}
