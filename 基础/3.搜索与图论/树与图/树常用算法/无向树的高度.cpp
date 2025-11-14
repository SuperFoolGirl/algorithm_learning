// 每一个点都要作为根节点

#include <algorithm>
#include <cstring>
#include <iostream>


using namespace std;

typedef long long LL;

const int N = 1e5 + 10;

int h[N], e[N], ne[N], idx;
int he[N];    // 统计全局高度

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

// 注意，考虑递归问题时，要注重本层的意义
// 换句话说，就是“height的功能就是返回当前节点的高度”
// 尽管还没实现，但要相信这个递归函数就是能够实现
// 不要陷入深度遍历内部的错误方向

// 这又是一个后序遍历的例子，进而自底向上地完成递归
int height(int r, int fa) {
    int maxh = 0;
    for (int i = h[r]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) {
            continue;
        }
        // 对于每个子树，根据其高度更新当前节点的最大高度
        maxh = max(maxh, height(j, r));
    }
    // 返回当前节点的高度
    return maxh + 1;
}

int main() {
    memset(h, -1, sizeof h);
    int n;
    cin >> n;

    // 树的边数是n-1，构建无向图
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
        add(b, a);
    }

    // 求每个节点的高度
    for (int i = 1; i <= n; i++) {
        // i作为根节点
        he[i] = height(i, 0);
        cout << he[i] << endl;
    }

    return 0;
}
