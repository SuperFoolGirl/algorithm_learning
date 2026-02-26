// 1 2 3 题为同一类型，对于母题的变形不大，可以直接照搬

// 回顾最长上升子序列(LIS)问题
// f[i]表示以a[i]结尾的最长上升子序列的长度
// DP集合划分常用依据：最后一个不同的点（重点）
// 虽然DP问题经常考虑“最后一步”，但这里f的定义就是最后一步了，因此向前考虑倒数第二步
// 枚举序列倒数第二个数a[j]，其中j<i. 若a[j]<a[i]，则f[i] = max{f[i],f[j]+1}


// 题目描述
// 水平方向，起点任意，方向左右但只能确定一个方向，不得回头；每一步严格单调下降，求最大步数
// 题目解析
// 两个方向，其实就是正着处理数组和倒着处理数组而已

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 110;

int n;
int h[N];
int f[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int k;
    cin >> k;
    while (k--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> h[i];
        }

        int res = 0;
        // 正向LIS
        for (int i = 1; i <= n; i++) {
            // 初始化：以a[i]结尾的最长上升子序列至少包含a[i]自己
            f[i] = 1;
            for (int j = 1; j < i; j++) {
                if (h[j] < h[i]) {
                    f[i] = max(f[i], f[j] + 1);
                }
                res = max(res, f[i]);
            }
        }

        // 反向LIS
        for (int i = n; i >= 1; i--) {
            // 初始化：以a[i]结尾的最长上升子序列至少包含a[i]自己
            f[i] = 1;
            for (int j = n; j > i; j--) {
                if (h[j] < h[i]) {
                    f[i] = max(f[i], f[j] + 1);
                }
                res = max(res, f[i]);
            }
        }

        cout << res << endl;
    }

    return 0;
}
