// head = 边，e[边] = 值，ne[边] = 边。其中ne[x] = -1表示x是链表的尾节点。
// 通过ne数组串联起整条链表，可以类比一下字典树的参数1
// 就这样，用两个数组来模拟一个单链表，即静态链表
// 邻接表就是一组单链表的集合，用于存储树、图

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 1e5 + 10;
int head;
int e[N], ne[N], idx;    // idx是当前链表的索引，始终指向下一个空闲位置

// 初始化
void init() {
    head = -1;    // 初始化链表头
    idx = 0;      // 初始化索引
}

// 头插法
void add_to_head(int x) {
    e[idx] = x;        // 将值存入e数组
    ne[idx] = head;    // 将当前节点的next指向原来的头节点
    head = idx++;      // 更新头节点为当前节点，并将idx加1
}

// 将x插到下标为k的点的后面
void add(int k, int x) {
    e[idx] = x;         // 将值存入e数组
    ne[idx] = ne[k];    // 将当前节点的next指向k的next
    ne[k] = idx++;      // 将k的next指向当前节点，并更新idx
}

// 将下标为k的点的后面的点删除
void remove(int k) {
    ne[k] = ne[ne[k]];    // 将k的next指向k的next的next，跳过被删除的节点
}

int main() {
    init();
    return 0;
}
