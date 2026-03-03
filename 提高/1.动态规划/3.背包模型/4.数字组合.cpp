// 01背包的简单应用，属性为计数
// 花费：数字总和

// 状态表示
// 集合：所有从前i个物品中选，且总花费恰好为j的方案
// 属性：计数
// 状态计算
// f(i,j) = f(i-1,j) + f(i-1,j-v[i])

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;

int n, m;
int f[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    // 根据定义初始化
    // f[i][0] = 1
    // f[i][m] = 0
    f[0] = 1;
    for (int i = 1; i <= m; i++) {
        f[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int v;
        cin >> v;
        for (int j = m; j >= v; j--) {
            f[j] += f[j - v];
        }
    }

    cout << f[m] << endl;

    return 0;
}
