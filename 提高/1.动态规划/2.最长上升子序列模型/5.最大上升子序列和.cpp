// 相比LIS，本题不再求序列长度，而是求序列和
// 写法上很简单，思路与母题是高度一致的

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int N = 1e5 + 10;

int n;
int w[N];
int f[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    int res = 0;
    for (int i = 1; i <= n; i++) {
        f[i] = w[i];
        for (int j = 1; j < i; j++) {
            if (w[j] < w[i]) {
                f[i] = max(f[i], f[j] + w[i]);
            }
        }
        res = max(res, f[i]);
    }

    cout << res << endl;

    return 0;
}
