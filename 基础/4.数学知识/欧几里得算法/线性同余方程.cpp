// 给定n组a_i, b_i, m_i,对每组数求一个x_i,使其满足 a_i * x_i ≡ b_i (mod m_i)
// 可以这样翻译：a和x的乘积模m，结果是b

// 这个题是求解一次线性同余方程
// 回忆下离散Ⅰ做法，首先判断解的数量
// 1. b是m的倍数，解的数量为d(a, m)
// 2. b不是m的倍数，无解
// 求解 a/d * x ≡ b/d (mod m/d)
// 对a，m列qrst表格，解出s,t满足扩展欧几里得定理，x=sb即可

// 本算法中不引入s,t，做法与离散Ⅰ不同
// 将ax ≡ b (mod m) 转化为 ax - my = b 的形式，即
// ax - my = b
// 这就是扩展欧几里得算法的形式
// 有解的判断条件：gcd(a, m) | b，这一点与离散相同

// 这里再介绍一个使用逆元来解方程的方法
// ax≡b(mod m)。如果 gcd(a,m)=1，那么 x≡b⋅a^(-1)(mod m)。
// a的逆元求法：ax≡1(mod m)的x，用扩展欧几里得算法求解得到x
// 那么其实这里的求解，就是列表格得到的s
// 扩展欧几里得算法是一个凑线性组合的过程，离散借助的是列表，算法借助的是递归

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10;

int exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

int main() {
    int a, b, m;
    cin >> a >> b >> m;
    int x, y;
    int d = exgcd(a, m, x, y);    // 要得到ax+my=d

    // 有解的判断条件，解为x
    if (b % d) {
        cout << "impossible" << endl;
    } else {
        int res = ((LL)x * (b / d)) % m;
        // 将可能为负数的res调整到[0, m)范围内
        if (res < 0) {
            res += m;
        }
        cout << res << endl;
    }
    return 0;
}
