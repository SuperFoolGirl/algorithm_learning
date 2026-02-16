// 每个物品i有各自的选择次数限制s[i]，因此和完全背包很相似
// 二者暴力写法是几乎一样的。不过优化有差异
// 这里用到二进制优化法，具体原理请回顾视频。简单来说，就是用二进制来表示任何一个十进制数
// 假设s[i]=1023，就不需要枚举1024次，而是枚举其指数0~9共10个数即可。在代码中做的就是转化为二进制
// 这样，枚举量就从s[i]变成了log(s[i])，大大减少了枚举量

// 感性理解上，可以认为是把原物品进行打包
// 原先是n种物品，每种物品s[i]个，现在打包后是n*log(s[i])种物品，每种物品1个，变成了01背包问题
// 这就是能够转化01背包的理论支撑

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10;

int w[N], v[N], f[N];
int n, m;

int main() {
    cin >> n >> m;

    // cnt变量记录打包后的物品数量，v数组记录打包后物品的体积，w数组记录打包后物品的价值
    // 每个s都要进行二进制打包，打包后的物品数量不超过n*log(s[i])，因此cnt的上限是n*log(s[i])
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        // 共n个物品，每次输入一个物品的体积a、价值b和数量s
        int a, b, s;
        cin >> a >> b >> s;
        int k = 1;    // 二进制的起始，即2^0
        // 下面实际上是求十进制数s的二进制表示
        while (k <= s) {
            // 每次把k个物品打包在一起，将其看成一个新的物品，体积是a*k，价值是b*k
            cnt++;
            v[cnt] = a * k;
            w[cnt] = b * k;
            s -= k;
            k *= 2;
        }
        if (s > 0) {    // 二进制最后的收尾，不规则，只有一次
            cnt++;
            v[cnt] = a * s;
            w[cnt] = b * s;
        }
    }

    n = cnt; // 更新物品数量为打包后的数量

    // 至此，下面就是标准的01背包问题了
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= v[i]; j--) {
            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }
    }

    cout << f[m] << endl;

    return 0;
}
