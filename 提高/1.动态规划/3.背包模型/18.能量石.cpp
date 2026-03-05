// 对于这种复杂的题，往往需要先用贪心去挖掘一些题目的性质
// 对于本题，隐藏性质是比值排序，这里不赘述
// 之后就是01背包问题了

// 状态表示 f(i,j)
// 集合：排序后，所有从前i块能量石中选，且总时间恰好是j的选法(恰好模型，之所以采用这个是因为符合题意)
// 属性：max
// 状态计算
// f(i,j) = max{ f(i-1,j), f(i-1,j-s)+e-(j-s)*l }
// 解读一下，e是第i块能量石的初始能量，吃完它的时刻是j，吃它所需要的时间是s，因此开始吃它的时刻是j-s，损失掉了(j-s)*l的能量
// 可以发现，为了贴合这段解读，必须采用恰好模型，以达到精准的时刻控制

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 10010;

int n;
int f[N];
struct Stone {
    int s, e, l;
    bool operator<(const Stone& t) const {
        // 题目隐含的性质：比值排序，即Si/Li < Si+1/Li+1
        return s * t.l < l * t.s;
    }
} stone[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        // m为总时间，即吃完所有能量石所需要的时间
        int m = 0;
        for (int i = 0; i < n; i++) {
            cin >> stone[i].s >> stone[i].e >> stone[i].l;
            m += stone[i].s;
        }

        sort(stone, stone + n);

        // 恰好模型初始化
        memset(f, -0x3f, sizeof f);
        f[0] = 0;
        for (int i = 0; i < n; i++) {
            int s = stone[i].s, e = stone[i].e, l = stone[i].l;
            for (int j = m; j >= s; j--) {
                f[j] = max(f[j], f[j - s] + e - (j - s) * l);
            }
        }

        // 恰好模型需要自己找最大值，f[m]不一定是最优解，原理在16题说过
        int res = 0;
        for (int j = 0; j <= m; j++) {
            res = max(res, f[j]);
        }

        cout << res << endl;
    }

    return 0;
}
