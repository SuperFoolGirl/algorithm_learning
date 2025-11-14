// 直径是不依赖树的方向的
// 因此可以把任意节点作为根节点来计算直径
// 同时，构建为无向树

// 注意，这里的树是一般的树，不一定是二叉树
// 对于二叉树的经典直径算法，可以用有向树来实现
// 而对于一般树，则需要用无向树来实现

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10;

int h[N], e[N], ne[N], idx;

// 注意，he数组无法统计无向树意义下的全局高度
// 在代码中，将1号节点作为根节点传入函数
// 那么he数组统计的就是以1号节点为根节点的子树高度
int he[N];

int res;    // 维护直径答案

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

// 注意更新答案的时机
// 这里其实是先递归到叶子节点，然后回溯更新高度和答案
// 自底向上递推更新答案
// 这样就实现了非常类似动态树结构的效果
void diameter(int x, int fa) {
    for (int i = h[x]; i != -1; i = ne[i]) {
        int j = e[i];

        // 因为是无向图，所以要避免走回头路
        if (j == fa) {
            continue;
        }

        diameter(j, x);

        // 更新当前节点的两个最大高度
        // x的高度等于子树中最大高度+1
        he[x] = max(he[x], he[j] + 1);

        // 更新直径答案
        res = max(res, he[x] + he[j] + 1);
    }
}

int main() {
    memset(h, -1, sizeof h);
    int n;
    cin >> n;

    // 树的边数是n-1
    // 无向图中任何节点都可以作为根节点
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
        add(b, a);
    }

    // 参数一是假定的根节点，参数二是根节点的父节点
    diameter(1, 0);

    cout << res << endl;

    return 0;
}
