// 裴蜀定理，离散Ⅰ学过
// 对于任意正整数a,b，存在非零整数 x, y 使得 ax + by = gcd(a,b)
// 显然，当a，b互质时，ax + by = 1
// 给定算法扩展欧几里得定理，来求解上述a，b（离散Ⅰ是画表取倒数第二列来着）
int exgcd(int a, int b, int &x, int &y) {
    // 由欧几里得算法基本原理，gcd(a, b) = gcd(b, a % b).该算法是用递归进行描述的
    // 当b为0时，gcd(a,0)=a。在离散中，就可以倒回去找倒数第二列了
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);    // 反转xy有利于计算
    // 递归回来时，已经有by + (a mod b)x = d了
    // 因为 a mod b = a - ⌊a / b⌋ * b
    // 代入展开得到 ax + b(y - ⌊a / b⌋x) = d
    // x不用变，y要减去多余的部分
    y -= (a / b) * x;
    return d;
}
