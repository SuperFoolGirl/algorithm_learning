#include <algorithm>
#include <cstring>
#include <iostream>


using namespace std;

const int N = 1e5 + 10;

struct Node {
    int l = -1;
    int r = -1;
} tr[N];

int n;

void add(int a, int b) {
    if (tr[a].l == -1) {
        tr[a].l = b;
    } else {
        tr[a].r = b;
    }
}

void preOrder(int t) {
    if (t == -1) {
        return;
    }
    cout << t << " ";
    preOrder(tr[t].l);
    preOrder(tr[t].r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;

    int root = -1;
    // 处理n=1的情况（无任何边）
    if (n == 1) {
        root = 1;    // 唯一节点就是根
    } else {
        // 首次输入的边的a是根节点
        int a, b;
        cin >> a >> b;
        root = a;
        add(a, b);

        // 读取剩下的n-2条边
        for (int i = 0; i < n - 2; ++i) {
            cin >> a >> b;
            add(a, b);
        }
    }

    preOrder(root);

    return 0;
}
