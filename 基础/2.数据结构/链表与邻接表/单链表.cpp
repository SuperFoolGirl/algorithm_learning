// 用邻接表来实现
// 存储树、图 
// 用e[N] 来存储value，ne[N] 来表示某点的next。其中ne[x] = -1表示x是链表的尾节点。 
// 就这样，用两个数组来模拟一个链表

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;
int head;
int e[N], ne[N], idx; // idx是当前链表的索引，始终指向下一个空闲位置

// 初始化
void init() {
    head = -1; // 初始化链表头
    idx = 0; // 初始化索引
}

// 头插法
void add_to_head(int x) {
    e[idx] = x; // 将值存入e数组
    ne[idx] = head; // 将当前节点的next指向原来的头节点
    head = idx++; // 更新头节点为当前节点，并将idx加1
}

// 将x插到下标为k的点的后面
void add(int k, int x) {
    e[idx] = x; // 将值存入e数组
    ne[idx] = ne[k]; // 将当前节点的next指向k的next
    ne[k] = idx++; // 将k的next指向当前节点，并更新idx
}

// 将下标为k的点的后面的点删除
void remove(int k) {
    ne[k] = ne[ne[k]]; // 将k的next指向k的next的next，跳过被删除的节点
}

int main() {
    init();
    return 0;
}