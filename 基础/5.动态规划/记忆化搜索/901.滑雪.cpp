// 记忆化搜索
// 记忆化搜索是动态规划的一种实现方式，将循环的dp改成递归。使用数据结构来存储已经计算过的结果，以避免重复计算，从而提高效率。但时间复杂度略高于循环，且有爆栈风险
// 所有的动态规划题目都可以用递归来写，且递归更容易理解
// 树形dp是一种特殊的递归方式，这里给出更加一般的递归方式

// 题目说明
// 给定R行C列矩阵存储滑雪场区域的高度
// 一个人从滑雪场某个区域出发，每次可以上下左右任意方向滑动一个单位距离，前提是只能从高处移动到低处
// 求最长滑雪轨迹

// 状态表示
// 集合：f(i,j)表示以(i,j)为起点的滑雪轨迹
// 属性：max
// 状态计算
// 遍历周围四个方向，如果下一个位置的高度小于当前高度，那么就可以从(i,j)滑到下一个位置，f(i,j) = max(f(i,j), f(next_i, next_j) + 1)

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

int n, m;
int h[N][N];
int f[N][N]; // dp状态数组，同时作为记忆数组
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

// dp函数：求出f(i,j)并返回
int dp(int x, int y) {
    // 读取记忆
    if (f[x][y] != -1) {
        return f[x][y];
    }

    // 一开始还是dp初始化。最短的轨迹长度为1，即只包含起点
    f[x][y] = 1;
    // 计算状态
    for (int i = 0; i < 4; i++) {
        int a = x + dx[i];
        int b = y + dy[i];
        if (a >= 1 && a <= n && b >= 1 && b <= m && h[a][b] < h[x][y]) {
            f[x][y] = max(f[x][y], dp(a, b) + 1);
        }
    }

    return f[x][y];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> h[i][j];
        }
    }

    // 用-1标识状态未计算
    memset(f, -1, sizeof f);

    int res = 0;
    // 枚举起点
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            // dp函数：求出f(i,j)并返回
            res = max(res, dp(i, j));
        }
    }

    cout << res << endl;

    return 0;
}
