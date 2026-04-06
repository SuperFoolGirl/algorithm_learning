// 将所有结点分为两个集合
// 使得集合内部边权的最大值最小

// 根据描述，这并不是严格按照二分图来划分的，毕竟“集合内部仍然有边”
// 让我们来纠正一下吧
// 首先，提炼出二分背景，最大值最小问题，right版本
// 枚举mid作为答案时，应当满足这样的性质：把所有小于等于mid的边都删除，则剩下的应当是二分图
// 也就是说，大于mid的边在集合之间，小于等于mid的边在集合内部
// 我们要二分出来一个最小的mid
// 证明二分性：若mid可行，则(mid,R]作为答案也可行，进而有mid是最优答案，即最小的最大值

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 20010, M = 200010;

int n, m;
int h[N], e[M], ne[M], w[M], idx;
int color[N];  // 0未染色，1白色，2黑色

void add(int a, int b, int c) {
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

bool dfs(int u, int c, int x) {
    color[u] = c;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        // 若边权<=x，则认为这条边不存在
        if (w[i] <= x) {
            continue;
        }
        if (!color[j]) {
            if (!dfs(j, 3 - c, x)) {
                return false;
            }
        } else {
            if (color[j] == c) {
                return false;
            }
        }
    }
    return true;
}

bool check(int x) {
    memset(color, 0, sizeof color);
    // 二分图不要求连通，因此需要遍历所有的联通分块
    for (int i = 1; i <= n; i++) {
        if (!color[i]) {
            if (!dfs(i, 1, x)) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    memset(h, -1, sizeof h);

    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);
    }
    
    // 如果本身就是二分图，这种情况需要特判一下——答案是0
    // 在本题中，如果本就是二分图，不论传入什么mid，check都返回true，因此二分出来的答案恰好就是0，不用特判了
    int l = 0, r = 1e9;
    while (l < r) {
        int mid = l + r >> 1;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    cout << l << '\n';

    return 0;
}
