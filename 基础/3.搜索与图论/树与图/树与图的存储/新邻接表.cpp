// 边计数器idx改为从1开始
// 具体操作为add中第一次使用时前置++，与二叉树的idx类似
// 由于h数组中存储的是边的编号，所以默认初始化为0即代表没有出边
// 省去了memset将h尾指针初始化为-1的步骤
// 同时idx直接表示所有边的数量（虽然题目一般直接给出为m）

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10, M = N * 2;

int h[N], e[M], ne[M], idx;
int n, m;

void add(int a, int b) {
    e[++idx] = b;  // 先自增idx，再使用
    ne[idx] = h[a];
    h[a] = idx;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    // h数组默认初始化为0，无需memset
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
    }

    return 0;
}
