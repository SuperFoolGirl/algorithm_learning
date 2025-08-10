// 给定一个字符串，任取其中的两段，询问这两段是否相同
// 做法：对于字符串的所有前缀，分别求哈希值
// 例如字符串abcde，前缀有a，ab，abc，abcd，abcde
// 这五个前缀的哈希值分别为h1，h2，h3，h4，h5

// 关于字符串片段哈希值的求法：
// 将整个字符串看作是一个p进制的数，左边是高位，右边是低位
// 对于h[x]，就是前左x位数，权重从大到小为p^(x-1), p^(x-2), ..., p^0
// 如何计算h[R] - h[L-1]呢？
// 1. 对其h[R]和h[L-1]的位数，使得二者位数相同。即将h[L-1] × p^(R-L+1)
// 2. 计算h[R] - h[L-1] × p^(R-L+1)，即为结果

// 这个结果，最高位就不是从最左边开始了
// 不理解的话，可以写一个数来类比一下：
// 12345678，求中间345
// 那么就是12345-12*10^3=345，完美契合

// 而前缀哈希值的求法，用循环的方法：h[i] = h[i-1] * p + s[i]，很眼熟

// 题目：
// 输入n字符串长度，m询问次数，s原字符串
// 每轮询问，给定l1,r1,l2,r2，询问s[l1..r1]和s[l2..r2]是否相同

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

// 这里讲一下无符号数的使用技巧
// 如果用无符号数存储一个越界的变量，会实现自动取模的操作
// 也就是说，会将右值对2^64取模后进行存储
typedef unsigned long long ULL;

// P取131或1331
const int N = 1e5 + 10, P = 131;
int n, m;
char str[N];
// p数组用来存P的幂，省去每次询问的开支
ULL h[N], p[N];

ULL get_hash(int l, int r) {
    return h[r] - h[l - 1] * p[r - l + 1];
}

int main() {
    // 还是注意字符串的读入方式，从下标为一开始读
    cin >> n >> m >> str + 1;

    // 计算p数组
    p[0] = 1;
    for (int i = 1; i <= n; i++) {
        h[i] = h[i - 1] * P + str[i];    // 这里直接借助ascii码值来计算哈希值了
        p[i] = p[i - 1] * P;
    }
    while (m--) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        ULL hash1 = get_hash(l1, r1);
        ULL hash2 = get_hash(l2, r2);
        if (hash1 == hash2) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }

    return 0;
}
