// 登山的变形

// 题目分析
// 队列要求身高从左到右，下降前一直上升，呈现两边单调，与上一题登山一致
// 去掉k名同学后，能够出现该态势，那么实际上求的内容与登山是一致的，两个问题是对偶的

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

int n;
int h[N];
int f[N], g[N];

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

    // 对偶性
    cout << n - res << endl;

    return 0;
}
