// 二维区间DP

// 分析题意：
// 本题除了二维表示占4维，还有切分次数这一维度，因此是5维的DP问题
// x拔：这里可以用到二维前缀和
// xi拔：在对应子矩阵中求平均数即可
// 切法：横切和纵切
// 其中，横切和纵切还能各自分成若干类，根据矩阵大小枚举切分点
// 一刀切成两份，选择哪份也是不同的方案(因为两部分中只有一部分能继续切分下去)
// 已知棋盘为8*8，以第一刀为例
// 横着切，7种方案，选择上下*2，共14种；竖着切同理14种

// 状态表示 f(x1,y1,x2,y2,k)
// 集合：子矩阵(x1,y1)(x2,y2)切分k次的所有方案
// 属性：min
// 状态计算
// 本题循环太复杂，因此不用迭代法，来试试记忆化搜索
// 记忆化搜索一直比循环dp更好写，尤其是多维dp，虽然递归效率差一些
// 做久了迭代DP，记忆化搜索有点忘了：顺序和迭代相反
// 迭代是从起点一步步递推到终点
// 递归是从终点一点点拆分到起点(基准)，然后一把全搂回来
// 因此，要计算f(1,1,m,m,n)，就不断把它递归下去

// 回忆DP与图论的关系
// 循环DP的点扩展，可以看作是从起点开始，枚举每个点的入边，进而构建路径，给人“扯着向前”的感觉
// 而递归DP的点扩展，则是从终点开始，枚举每个点的入边来构建路径。对于反向跑图来说，是更加自然的方式，就像“从起点开始枚举出边”一样
// 但由于都是枚举点的入边(即由什么更小的子状态转移而来)，因此状态转移方程在迭代和递归中都是差不多的
// 因此这里可以进一步抽象：将子-父关系视为入边->点

#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>


using namespace std;

const int N = 15, M = 9;
const double INF = 1e9;

int n, m = 8;
int s[M][M];
double f[M][M][M][M][N];
double X;

// 求均方差
double get(int x1, int y1, int x2, int y2) {
    double sum = s[x2][y2] - s[x2][y1 - 1] - s[x1 - 1][y2] + s[x1 - 1][y1 - 1] - X;
    return sum * sum / n;
}

double dp(int x1, int y1, int x2, int y2, int k) {
    // 别名
    double& v = f[x1][y1][x2][y2][k];
    // 记忆化搜索
    if (v >= 0) {
        return v;
    }
    // k=1说明不能再切了
    if (k == 1) {
        return v = get(x1, y1, x2, y2);
    }

    // 属性为min的初始化
    v = INF;
    // 横切
    for (int i = x1; i < x2; i++) {
        // 选上面(上面的继续切，继续递归；下面的不动了，作为完整的一份)
        v = min(v, dp(x1, y1, i, y2, k - 1) + get(i + 1, y1, x2, y2));
        // 选下面
        v = min(v, dp(i + 1, y1, x2, y2, k - 1) + get(x1, y1, i, y2));
    }
    // 纵切
    for (int i = y1; i < y2; i++) {
        // 选左面
        v = min(v, dp(x1, y1, x2, i, k - 1) + get(x1, i + 1, x2, y2));
        // 选右面
        v = min(v, dp(x1, i + 1, x2, y2, k - 1) + get(x1, y1, x2, i));
    }

    return v;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> s[i][j];
            s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
        }
    }

    // 用于记忆化搜索
    memset(f, -1, sizeof f);

    X = (double)s[m][m] / n;

    printf("%.3f", sqrt(dp(1, 1, 8, 8, n)));

    return 0;
}
