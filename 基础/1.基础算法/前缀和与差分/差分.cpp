// 差分是前缀和的逆运算

// 构造b1, b2, ..., bn
// 使得ai = b1 + b2 + ... + bi
// 即a是b的前缀和，通过前缀和相减即可求出b
// 那么有：
// b1 = a1
// b2 = a2 - a1
// b3 = a3 - a2
// ...
// bn = an - a(n-1)
// 可见，对bi求前缀和，就得到ai

// 作用：通过改变差分数组b的元素，来改变原数组a的区间值
// 举例，如果b[l]+x，那么a[l]到a.back()的值都加上x
// 这个效率是O(1)的，如果挨个给a加，那就是O(n)
// 如b[l]+=x, b[r+1]-=x, 那么就实现了原数组a对区间[l, r]每个元素都加了x

#include <algorithm>
#include <cstring>
#include <iostream>


using namespace std;

const int N = 1e5 + 10;
int a[N], b[N];
int n, m;

void insert(int l, int r, int c) {
    b[l] += c;        // 从l开始加c
    b[r + 1] -= c;    // 从r+1开始减去c
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        // 初始化差分数组
        // b[i] = a[i] - a[i - 1];
        insert(i, i, a[i]);    // 法二
    }

    while (m--) {
        int l, r, c;
        cin >> l >> r >> c;
        insert(l, r, c);    // 区间[l, r]加c
    }

    // 计算前缀和，得到原数组
    // 在不断循环++i中，b[i-1]不断更新为新的前缀和
    // 这里一步步加，使得每一位b[i]都变成了前缀和a[i]
    for (int i = 1; i <= n; ++i) {
        b[i] += b[i - 1];    // 前缀和
    }
    // 经过上述操作，将b数组完全变成了a数组
    for (int i = 1; i <= n; ++i) {
        cout << b[i] << " ";    // 输出结果
    }

    return 0;
}
