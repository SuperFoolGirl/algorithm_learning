/*
先讲一些性质
1. 模运算
(a · b) % p = [(a % p) · (b % p)] % p
2. 关于快速幂
快速幂的思路是把指数n转为二进制形式，例如，计算a^11，11的二进制是1011，也就是
11 = 1 * 2^3 + 0 * 2^2 + 1 * 2^1 + 1 * 2^0
所以可以转化为a^11 = a^(1 * 2^3) * a^(0 * 2^2) * a^(1 * 2^1) * a^(1 * 2^0)
由于是二进制，每位要么是0，要么是1，所以可以用位运算来判断每一位是否为1
*/

#include <iostream>
using namespace std;

// 快速幂函数，计算a的b次方
long long fastPower(int a, int b)
{
    long long result = 1;
    while (b > 0)
    {
        // 如果b的二进制位最后一位是1，那这一位得乘进去
        if (b & 1)
        {
            result *= (long long)a;
        }

        // 让a自乘，a的幂次变为原来的2倍：a变成a^2，a^2变成a^4，来模拟快速幂指数处的变化
        // 每轮都要执行，不管乘没乘进去
        a *= a;
        // 右移b，相当于b除以2，用于检查下一位二进制位
        b >>= 1; // 复合运算操作符，b = b / 2
    }
    return result;
}
int main()
{
    int base = 3;
    int exponent = 5;
    long long result = fastPower(base, exponent);
    cout << base << " 的 " << exponent << " 次方是: " << result << endl;
    return 0;
}