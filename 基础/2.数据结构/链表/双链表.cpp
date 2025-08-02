#include <algorithm>
#include <cstring>
#include <iostream>


using namespace std;

const int N = 1e5 + 10;
int m;
int e[N], l[N], r[N], idx;

void init() {
    // 0号节点是头节点，1号节点是尾节点
    r[0] = 1;    // 0号节点的右指针指向1(tail)
    l[1] = 0;    // 1号节点的左指针指向0(head)
    idx = 2;     // 从2号节点开始使用
}

// 把x插在k后面
// 如果想把x插在k的前面，那传参时，参数一可以传k的左指针l[k]（不是k-1）
void add(int k, int x) {
    e[idx] = x;
    r[idx] = r[k];
    l[idx] = k;
    // 下面不能反
    l[r[k]] = idx;
    r[k] = idx++;
}

// 删掉k这个节点（不是删掉k后面那个）
void remove(int k) {
    r[l[k]] = r[k];
    l[r[k]] = l[k];
}

int main() {
    init();
    return 0;
}
