// 状态表示f(i,j)
// 集合：所有从(1,1)到(i,j)的路线
// 属性：max

// 状态计算
// 由于只能向下走或向右走，因此一个点的前驱只有两个：来自(i-1,j)或(i,j-1)
// f(i,j) = max{f(i-1,j),f(i,j-1)} + a[i][j]

// 这里再复习一下集合划分(状态计算)
// 原则：1.不重 2.不漏
// 其中，“不重”只有在属性为数量时才必须满足，“不漏”永远都需要满足
// 本题为求最值，最值可以不满足“不重”，但本题是满足的；对于复杂的题目，可能难以满足，但不影响结果

// 使用f和划分集合时，要严格按照自己给出的定义

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1010;

int n, m;
int w[N][N];
int f[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> w[i][j];
            }
        }

        // 初始化：(1,1)到(1,1)的路线只有一条
        f[1][1] = w[1][1];
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (i == 1 && j == 1) {
                    continue;
                } else {
                    f[i][j] = max(f[i - 1][j], f[i][j - 1]) + w[i][j];
                }
            }
        }

        cout << f[n][m] << endl;
    }

    return 0;
}
