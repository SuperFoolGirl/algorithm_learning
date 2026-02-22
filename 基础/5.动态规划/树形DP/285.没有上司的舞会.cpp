// n名职员，编号1~n
// 父结点是子结点的直接上司，根结点是老板
// 每个职员有一个快乐指数，用h[i]表示第i个职员的快乐指数
// 公司舞会要举办了，不过没有职员愿意和上司一起参会
// 满足该条件的前提下，如何让所有参会职员的快乐指数最大？

// 第一行输入n
// 接下来n行输入h[i]
// 接下来n-1行输入一对整数l,k，表示k是l的直接上司
// 最后一行输入0 0



// dp问题要保证计算当前状态时，其子状态已经被计算出来了
// 在树形dp中，这一点的体现在于计算一个结点的状态时，其子结点的状态已经被计算出来了
// 因此，树形dp的计算顺序是从下往上计算的

// 状态表示
// f(u,0)表示所有以u为根的子树中选择，且不选u的方案
// f(u,1)表示所有以u为根的子树中选择，且选u的方案
// 属性为max
// 状态计算
// 设结点u的子结点为s1，s2，...，sk
// 求f(u,0):
// 当u不选时，其子结点可以选择(也可以不选)
// 即f(u,0)=sum(max(f(s1,0),f(s1,1)), max(f(s2,0),f(s2,1)), ..., max(f(sk,0),f(sk,1)))
// 求f(u,1):
// 当u选时，其子结点一定不能选
// 即f(u,1)=h[u]+sum(f(s1,0), f(s2,0), ..., f(sk,0))

// 时间复杂度：需要访问所有的儿子，也就是访问所有结点，因此是O(n)

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10;

int n;
int happy[N];
int h[N], e[N], ne[N], idx;
int f[N][2];
// 需要自己求出根结点，借助辅助数组has_father
bool has_father[N];

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

void dfs(int u) {
    // 如果选择这个点，那么这个方案先加上此人的快乐指数
    // 每个点只会跑一次dfs，因此进来时f[u]必为0，这里可以用等号
    f[u][1] = happy[u];

    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        // 先算儿子，将作为自己的计算依据
        dfs(j);

        // 每算出一个儿子就更新一次，这样是合法的，因为就是要对每个儿子进行计数操作
        // 递归保证子状态一定是最终确定的结果
        f[u][0] += max(f[j][0], f[j][1]);
        f[u][1] += f[j][0];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> happy[i];
    }

    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        has_father[a] = true;
        add(b, a);
    }

    // 求根结点
    int root = 1;
    while (has_father[root]) {
        root++;
    }

    // 上面提到了，树形dp的计算是自底向上的
    // 而树的常规操作就是递归，因此树形dp的计算顺序就是递归的顺序，即先访问子结点，再访问父结点
    dfs(root);

    // 最终的答案，肯定要落到根结点上。根结点可以选，也可以不选，因此取两者的最大值
    cout << max(f[root][0], f[root][1]) << endl;

    return 0;
}
