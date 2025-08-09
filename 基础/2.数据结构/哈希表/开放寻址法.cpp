// 维护一个集合，支持如下操作：
// 1. I x，插入一个数x
// 2. Q x，询问一个数x是否在集合中

// 开放寻址法，回忆数据结构，需要标识某个位置是否被占用
// 这里用一次探测即可
// 这里初始化为0x3f3f3f3f

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10, flag = 0x3f3f3f3f;
int h[N];
// 给定n次询问
int n;

// 插入、查询二合一
// 如果x在哈希表内，就返回它的位置
// 如果不在，就返回它应该插入的位置
int find(int x) {
    int k = (x % N + N) % N;
    while (h[k] != flag && h[k] != x) {
        k++;    // 一次探测
        // 所有位置都看过了，那就回到开头
        if (k == N) {
            k = 0;    // 环形处理
        }
    }

    return k;
}

int main() {
    cin >> n;

    // 初始化哈希表
    memset(h, 0x3f, sizeof h);

    while (n--) {
        char op[2];
        int x;
        cin >> op >> x;
        int k = find(x);

        if (*op == 'I') {
            h[k] = x;    // 插入
        } else {
            // flag是一个占位符，表示该位置未被使用。数组会初始化为flag
            if (h[k] != flag) {
                puts("Yes");
            } else {
                puts("No");
            }
        }
    }

    return 0;
}
