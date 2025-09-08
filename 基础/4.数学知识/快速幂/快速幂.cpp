/*
先讲一些性质
1. 模运算
(a · b) % p = [(a % p) · (b % p)] % p
2. 关于快速幂
快速幂的思路是把指数n转为二进制形式，例如，计算a^11，11的二进制是1011，也就是
11 = 1 * 2^3 + 0 * 2^2 + 1 * 2^1 + 1 * 2^0
所以可以转化为a^11 = a^(1 * 2^3) * a^(0 * 2^2) * a^(1 * 2^1) * a^(1 * 2^0)
可以看到，指数被分解成了若干个2的幂次，这也是qmi函数中a = (a * a) % p的原因
由于是二进制，每位要么是0，要么是1，所以可以用位运算来判断每一位是否为1
*/

#include <iostream>

using namespace std;

typedef long long LL;

// Quick Multiple Inversion
// a^b%p
// 由于返回取模的结果，因此返回值是int类型
int qmi(int a, int b, int p) {
    int res = 1;    // 2^0
    while (b) {
        // 遍历b的每一位，b的二进制01就代表取或不取
        if (b & 1) {
            res = (LL)res * a % p;
        }
        // 不论这一轮a用不用，都是要自乘的。因为分解a^b时，分解的项总是a^0,a^2,a^4...即a^(2^k)的形式
        // 而这可以用自乘来得到每一轮的项，然后由b这一位的01情况来选择是用还是不用
        a = (a * a) % p;
        b >>= 1;    // 复合运算操作符，b = b / 2
    }
    return res;
}

int main() {
    int a, b, p;
    cin >> a >> b >> p;

    int res = qmi(a, b, p);
    cout << res << endl;

    return 0;
}
