// 找到根节点后，逻辑上就很类似动态二叉树的算法了

// 注意，树高与树的方向性是相关的
// 对于无向树来说，每个节点都可以作为根节点
// 因此，当计算无向树的高度时，需要将每个点都视为根节点，来计算其高度
// 而对于有向树来说，根节点是唯一的，因此高度的计算只需要从唯一的根节点出发即可

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
