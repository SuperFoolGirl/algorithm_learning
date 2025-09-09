#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;
int n, m;
int a[N], s[N];

int main() {
    cin >> n >> m;
    // 前缀和数组，s[i]表示前i个数的和。注意细节，循环变量i从1开始
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
    }

    // 输出l到r的和，进行m次询问
    while (m--) {
        int l, r;
        cin >> l >> r;
        cout << s[r] - s[l - 1] << endl;
    }

    return 0;
}