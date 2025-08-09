// 维护一个集合，支持如下操作：
// 1. I x，插入一个数x
// 2. Q x，询问一个数x是否在集合中

// 这里使用拉链法，注意用数组模拟的写法

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10;
// h是槽，每个槽要拉一个链表出来
// 所有节点都放在e中，而不是每个槽都要开一个e ne数组来模拟一条单链表
// 虽然不如传统的动态拉链直观，但这样的确是可以准确映射的
int h[N], e[N], ne[N], idx;
// 给定n次询问
int n;

void insert(int x) {
    // 计算哈希值
    // x % N + N：负数取模为负数，所以加个N统一为正数，然后后面再模运算一次
    int k = (x % N + N) % N;
    e[idx] = x;
    // 插入到链表头部，也就是头插
    ne[idx] = h[k];
    h[k] = idx++;
}

bool query(int x) {
    int k = (x % N + N) % N;
    // h[k]作为表头，记录插入时idx的情况。此条链表的尽头空节点为-1
    for (int i = h[k]; i != -1; i = ne[i]) {
        if (e[i] == x) {
            return true;
        }
    }
    return false;
}

int main() {
    // 数据范围是100000，找到>=100000的第一个质数作为表长。这里略过查询步骤，结果是100003
    cin >> n;
    while (n--) {
        char op[2];
        int x;
        cin >> op >> x;

        if (*op == 'I') {
            insert(x);
        } else {
            if (query(x)) {
                puts("Yes");
            } else {
                puts("No");
            }
        }
    }

    return 0;
}
