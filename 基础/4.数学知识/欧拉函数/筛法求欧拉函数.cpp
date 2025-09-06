// 给定n，求1~n中每个数的欧拉函数之和

// 在筛法求质数的过程中，求出每个数的欧拉函数
// 先搬过来线性筛法代码
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10;

int primes[N], cnt;
int phi[N];
bool st[N];

// 线性筛代码
LL get_eulers(int n) {
    // 1的欧拉函数要特别定义
    phi[1] = 1;

    for (int i = 2; i <= n; i++) {
        if (!st[i]) {
            primes[cnt++] = i;
            // 如果一个数p是质数的话，其欧拉函数为p-1，与1~p-1全部互质
            phi[i] = i - 1;
        }
        for (int j = 0; primes[j] <= n / i; j++) {
            st[primes[j] * i] = true;
            // 1. 当pj是i的质因子时，即i mod pj == 0时，则pj*i与i的质因子完全相同
            //    相比i，pj*i只是多了一个pj，在欧拉公式开头N补上即可，后面的质因子系列项完全相同
            // 2. 当i mod pj != 0时，pj不再是i的质因子了，所以质因子系列项最后加一个(1 - 1/pj)，当然开头也要补pj
            //    即在phi[i]基础上×pj×(1 - 1/pj)，即×(pj-1)
            if (i % primes[j] == 0) {
                phi[primes[j] * i] = phi[i] * primes[j];
                break;
            } else {
                phi[primes[j] * i] = phi[i] * (primes[j] - 1);
            }
        }
    }

    // 整理欧拉函数的和
    LL res = 0;
    for (int i = 1; i <= n; i++) {
        res += phi[i];
    }

    return res;
}

int main() {
    int n;
    cin >> n;

    cout << get_eulers(n) << endl;

    return 0;
}
