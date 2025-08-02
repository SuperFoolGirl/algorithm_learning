#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 1e5 + 10;
int stk[N], tt;

void init() {
    tt = 0;    // 初始化栈顶指针
}

void push(int x) {
    stk[tt++] = x;    // 将元素压入栈中，并更新栈顶指针
}

bool empty() {
    return tt == 0;    // 如果栈顶指针为0，表示栈为空
}

void pop() {
    if (empty()) {
        return;    // 如果栈为空，直接返回
    }
    tt--;          // 更新栈顶指针，表示弹出栈顶元素
}

int top() {
    if (empty()) {
        return -1;         // 如果栈为空，返回-1表示无元素
    }
    return stk[tt - 1];    // 返回栈顶元素。tt始终指向下一个空闲位置，所以栈顶元素在tt-1位置
}

int main() {
    init();
    return 0;
}
