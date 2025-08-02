// 保证栈的单调性
// 当不满足单调性时，弹出栈顶元素
// 这个模型只有放在具体题目里才有意义

// 题目：对于一个序列，求每个元素左边第一个比它小的元素的下标
// 如果没有比它小的元素，则返回 -1

#include <algorithm>
#include <cstring>
#include <iostream>


using namespace std;

const int N = 1e5 + 10;
int n;
int stk[N], tt = 0;    // 栈数组和栈顶指针

int main() {
    // 读入序列
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        // 保证栈的单调性
        // 如果栈不为空，且栈顶元素大于等于当前元素，则弹出栈顶元素
        // 因为栈顶元素将永远不会作为答案。可以证明，在后续（此时x已入栈）如果当栈顶可以作为答案时，那x一定是更优解
        while (tt && stk[tt - 1] >= x) { 
            tt--;                          // 弹出栈顶元素
        }
        if (tt) {
            cout << stk[tt - 1] << " ";    // 输出栈顶元素
        } else {
            cout << -1 << " ";             // 如果栈为空，输出 -1
        }
        // tt会停留在答案的位置，所以要在tt的下一位进行入栈
        stk[++tt] = x;                     // 将当前元素入栈
    }
    return 0;
}
