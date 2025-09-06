// 欧拉函数
// φ(n)为1-n中与n互质的数的个数
// 设n分解质因数的结果为p1, p2, ..., pk（各质因数的幂省略）
// φ(n) = n * (1 - 1/p1) * (1 - 1/p2) * ... * (1 - 1/pk)

// 该公式是基于容斥原理的思想，来计算1-n中与n互质的数的个数
// 1. 从1-n中去除p1,p2,...,pk的倍数，他们与n有公因子pi，必然不互质。共有n/p1 + n/p2 + ... + n/pk个数被去除
// 2. 第一步中会有重复的数被去除，把它们加回来，即所有pi*pj的倍数。共有n/(pi*pj)个数被加回来，i,j自由组合
// 3. 再去除所有pi*pj*pk的倍数...
// 4. 依次类推，将这些式子求和就是欧拉函数展开的结果

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

int phi(int n) {
    // 质因数分解
    int res = n;    // 欧拉公式的起点
    for (int p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) {
                n /= p;
            }
            res = res / p * (p - 1);    // 这行的写法是为了避免精度丢失
        }
    }
    if (n > 1) {
        res = res / n * (n - 1);
    }
    return res;
}

int main() {
    int num;
    cin >> num;

    int res = phi(num);

    cout << res << endl;

    return 0;
}
