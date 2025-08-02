#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 1e5 + 10;
int q[N], hh, tt;

void init() {
    hh = 0;    // 队头指针
    tt = 0;    // 队尾指针
}

void push(int x) {
    q[tt++] = x;    // 将元素入队，并更新队尾指针
}

bool empty() {
    return hh == tt;    // 如果队头指针等于队尾指针，表示队列为空
}

void pop() {
    if (empty()) {
        return;    // 如果队列为空，直接返回
    }
    hh++;          // 更新队头指针，表示出队
}

int front() {
    if (empty()) {
        return -1;    // 如果队列为空，返回-1表示无元素
    }
    return q[hh];     // 返回队头元素
}

int back() {
    if (empty()) {
        return -1;       // 如果队列为空，返回-1表示无元素
    }
    return q[tt - 1];    // 返回队尾元素。tt始终指向下一个空闲位置，所以队尾元素在tt-1位置
}

int main() {
    init();
    return 0;
}
