// 题目分析
// 1. 子序列
// 2. 高度严格单调
// 3. 一旦开始下降，就不能再上升
// 其中第三点与前两题不同，不是只找一边单调了
// 但其实，与怪盗基德是一样的，找两边就好了
// 只是，这里要用两个f/g来保存数据，正反向找完后再处理数据

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

int n;
int f[N], g[N];
int h[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    // 正向LIS
    for (int i = 1; i <= n; i++) {
        f[i] = 1;
        for (int j = 1; j < i; j++) {
            if (h[j] < h[i]) {
                f[i] = max(f[i], f[j] + 1);
            }
        }
    }

    // 反向LIS
    for (int i = n; i >= 1; i--) {
        g[i] = 1;
        for (int j = n; j > i; j--) {
            if (h[j] < h[i]) {
                g[i] = max(g[i], g[j] + 1);
            }
        }
    }

    // 处理数据
    int res = 0;
    for (int i = 1; i <= n; i++) {
        res = max(res, f[i] + g[i] - 1);
    }

    cout << res << endl;

    return 0;
}
