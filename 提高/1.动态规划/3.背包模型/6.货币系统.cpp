// 完全背包问题，和第五题买书是一模一样的
// 物品是n种不同面值的货币

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 20, M = 3010;

int n, m;
int f[M];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;

    // 用滚动数组优化，不需要存储货币面值

    // 本题问的是方案数，方案数取值为0/1，详细见readme
    f[0] = 1;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        for (int j = a; j <= m; j++) {
            f[j] += f[j - a];
        }
    }

    cout << f[m] << endl;

    return 0;
}
