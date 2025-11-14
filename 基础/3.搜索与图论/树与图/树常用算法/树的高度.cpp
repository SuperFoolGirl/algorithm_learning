// 找到根节点后，逻辑上就很类似动态二叉树的算法了
// 高度算法可以用有向图，也可以用无向图
// 这里使用有向图实现高度计算

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10;

int h[N], e[N], ne[N], d[N], idx;
int he[N];
int root;

void add(int a, int b) {
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

void height(int t) {
    // 循环边界控制会自动实现跳过空结点的效果

    for (int i = h[t]; i != -1; i = ne[i]) {
        int j = e[i];
        height(j);

        he[t] = max(he[t], he[j] + 1);
    }
}

int main() {
    memset(h, -1, sizeof h);
    int n;
    cin >> n;

    // 树的边数是n-1
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
        d[b]++;
    }

    // 找出根节点（入度为0）
    for (int i = 1; i <= n; i++) {
        if (d[i] == 0) {
            root = i;
            break;
        }
    }

    height(root);

    return 0;
}
