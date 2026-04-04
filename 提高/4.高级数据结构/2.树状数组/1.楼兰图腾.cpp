// 如何统计V字形图案个数？
// 用集合的思想
// 整个集合被分为n份：1,2,3,...,n，代表以i为低尖点的V字形图案
// 那么，统计1~i-1与i+1~n中大于i位置处元素的个数，就能得到结果了
// 我的集合思想还是太差了，本题结合坐标分类真的绝配

// 树状数组标志：
// 1.修改某个数
// 2.求区间和

#include <algorithm>
#include <cstring>
#include <iostream>


using namespace std;

typedef long long LL;

const int N = 200010;

int n;
int a[N], tr[N];    // a为原数组，tr为树状数组
int bigger[N], lower[N];  // bigger[i]表示1~i-1中大于a[i]的个数，lower[i]表示1~i-1中小于a[i]的个数

int lowbit(int x) {
    return x & -x;
}

void add(int x, int c) {
    for (int i = x; i <= n; i += lowbit(i)) {
        tr[i] += c;
    }
}

int sum(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) {
        res += tr[i];
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 本题并没有传统地初始化树状数组
    // 我们并不是要统计原数组a的区间和
    // add(y,1)是指在树状数组[1,n]中y的位置上+1，代表y这个数在集合中出现了
    // sum(x)是指在树状数组[1,n]中求前x个数的和，代表集合中小于等于x的数的个数

    // 正着做，把答案存在bigger和lower数组中
    for (int i = 1; i <= n; i++) {
        int y = a[i];
        bigger[i] = sum(n) - sum(y);    // 1~i-1中大于y的个数
        lower[i] = sum(y - 1);          // 1~i-1中小于y的个数
        add(y, 1);                      // 把y加入集合中
    }

    // 反着做，清空树状数组，统计答案时把bigger和lower请回来
    memset(tr, 0, sizeof tr);
    LL res1 = 0, res2 = 0;
    for (int i = n; i; i--) {
        int y = a[i];
        res1 += bigger[i] * (LL)(sum(n) - sum(y));    // 以i为高尖点的倒V字形图案个数
        res2 += lower[i] * (LL)sum(y - 1);            // 以i为低尖点的V字形图案个数
        add(y, 1);                                    // 把y加入集合中
    }

    cout << res1 << " " << res2 << "\n";

    return 0;
}
