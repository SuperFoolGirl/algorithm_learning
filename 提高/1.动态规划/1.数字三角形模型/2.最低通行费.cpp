// 2n-1说明不能走回头路，否则超步数
// 不过，在摘花生中，只能向下走或向右走，因此也不能走回头路
// 因此本题同摘花生，属性为min
// 对于max属性，f默认初始化为0；对于min，则需要手动置f为INF

#include <algorithm>
#include <cstring>
#include <iostream>


using namespace std;

const int N = 1010, INF = 0x3f3f3f3f;

int n;
int w[N][N];
int f[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> w[i][j];
        }
    }

    memset(f, 0x3f, sizeof f);

    // 初始化
    f[1][1] = w[1][1];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == 1 && j == 1) {
                continue;
            } else {
                f[i][j] = min(f[i - 1][j], f[i][j - 1]) + w[i][j];
                // 这里给出严格写法，按照规范可行路径
                // 原写法也正确，因为f[0][j]和f[i][0]已经初始化为INF了，因此可以数值过滤
                // 如果没有初始化f[0][j]和f[i][0]，则需要严格写法，否则越界访问会取到垃圾值0，破坏最小值结构
                // if (i > 1) {
                //     // 只有不在第一行时，才能从上面走下来
                //     f[i][j] = max(f[i][j], f[i - 1][j] + w[i][j]);
                // }
                // if (j > 1) {
                //     // 只有不在第一列时，才能从右边走过来
                //     f[i][j] = max(f[i][j], f[i][j - 1] + w[i][j]);
                // }
            }
        }
    }

    cout << f[n][n] << endl;

    return 0;
}
