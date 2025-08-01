#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;
int m;
int e[N], l[N], r[N], idx;

void init() {
    r[0] = 1; // 0号节点的右指针指向1(tail)
    l[1] = 0; // 1号节点的左指针指向0(head)
    idx = 2; // 从2号节点开始使用
}

int main() {

}
