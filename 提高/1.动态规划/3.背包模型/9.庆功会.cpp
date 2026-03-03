// 多重背包问题
// 花费：拨款，最大为m(花费一定作为状态数组的维度，最值与答案有关)

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 6010;

int n, m;
int f[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int v, w, s;
        cin >> v >> w >> s;
        for (int j = m; j >= v; j--) {
            for (int k = 0; k <= s && k * v <= j; k++) {
                f[j] = max(f[j], f[j - k * v] + k * w);
            }
        }
    }

    cout << f[m] << endl;

    return 0;
}
