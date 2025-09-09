// 原矩阵aij，构造差分矩阵bij
// 使得aij是bij的前缀和

#include <algorithm>
#include <cstring>
#include <iostream>


using namespace std;

const int N = 1e5 + 10;
int n, m, q;
int a[N][N], b[N][N];

void insert(int x1, int y1, int x2, int y2, int c) {
    // 画图理解，把图画出来是一目了然的。
    // b是参与求前缀和的元素
    // 既然b参与求前缀和，那审视b[x][y]时，就要以b[1][1]为左上角
    // b[x1][y1] += c后，所有包含(x1,y1)的前缀和都会加上c
    // 目标：只有在(x1,y1)到(x2,y2)这个区域内的所有点，其求前缀和时，整体会加一个c
    // 下面给出的四个点给出了特殊标记。如果所求的前缀和（以b[0][0]为左上角）包含了一个+c和一个-c，那么就相当于没有加
    // 这四句看似不明所以，实际画出图来就很清晰了。两组+c与-c的抗衡。
    b[x1][y1] += c;
    b[x2 + 1][y2 + 1] += c;
    b[x1][y2 + 1] -= c;
    b[x2 + 1][y1] -= c;
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
            // 这里的形式有点像动态规划。+=右边的东西，前面已经递推出来了
            // 不过这里完全可以理解成求二维前缀和，b的前缀和是a
            b[i][j] += b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1];
            cout << b[i][j] << " ";
        }
    }

    return 0;
}
