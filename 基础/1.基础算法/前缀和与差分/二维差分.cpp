// 原矩阵aij，构造差分矩阵bij
// 使得aij是bij的前缀和

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;
int n, m, q;
int a[N][N], b[N][N];

void insert(int x1, int y1, int x2, int y2, int c) {
    b[x1][y1] += c;          // 从(x1, y1)开始加c
    b[x2 + 1][y2 + 1] += c;  // 从(x2+1, y2+1)开始加c
    b[x1][y2 + 1] -= c;      // 从(x1, y2+1)开始减去c
    b[x2 + 1][y1] -= c;      // 从(x2+1, y1)开始减去c
}

int main() {
    cin >> n >> m >> q;
    // 初始化差分矩阵
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
            insert(i, j, i, j, a[i][j]);
        }
    }

    while (q--) {
        int x1, y1, x2, y2, c;
        cin >> x1 >> y1 >> x2 >> y2 >> c;
        insert(x1, y1, x2, y2, c);
    }

    // 计算前缀和，得到原矩阵a
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            // 这里的形式有点像动态规划
            // +=右边的东西，前面已经递推出来了。现在要基于这些数据，递推出b[i][j]
            // 至于计算二维前缀和的思路，可以参考对应代码/画图
            b[i][j] += b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1];
            cout << b[i][j] << " ";
        }
    }

    return 0;
}