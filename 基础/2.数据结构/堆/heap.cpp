// 堆的基本操作
// 维护一个heap数组
// 下标从1开始，父节点下标为i时，左子节点下标为2*i，右子节点下标为2*i+1

// 1. 插入一个数             heap[++size] = x; up(size); // 将新元素放到最后一个位置，然后上浮
// 2. 求集合中的最小值        heap[1];
// 3. 删除最小值             heap[1] = heap[size--]; down(1); // 将最后一个元素放到根节点，然后下沉
// 4. 删除任意元素           heap[k] = heap[size--]; down(k); up(k); // k变大了需要down，k变小了需要up，这里没有判断，而是都执行了
// 5. 修改任意元素的值       heap[k] = x; down(k); up(k);

// 堆排序：先把乱序数组构建成堆，然后不断取出最小值
// 题目：给定n个元素数组，输出前m小的元素

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10;
int n, m;
int h[N], sz;

void down(int x) {
    int t = x;    // 记录当前节点、左子节点、右子节点中最小值的下标
    if (2 * x <= sz && h[2 * x] < h[t]) {
        t = 2 * x;
    }
    if (2 * x + 1 <= sz && h[2 * x + 1] < h[t]) {
        t = 2 * x + 1;
    }
    // 最后，t存的就是三个点里最小的

    if (t != x) {    // 如果当前节点不是最小值，就和最小值交换，然后继续下沉
        swap(h[t], h[x]);
        down(t);
    }
}

void up(int x) {
    if (x / 2 && h[x / 2] > h[x]) {    // 如果当前节点不是根节点，且父节点大于当前节点
        swap(h[x / 2], h[x]);
        // 交换后继续上浮，直到找到正确的位置
        up(x / 2);
    }
}

void del_min() {
    h[1] = h[sz--];
    down(1);
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }
    sz = n;

    // 建堆
    // 从倒数第二层开始down，叶子节点本来就在最下面，不需要down
    for (int i = n / 2; i; i--) {
        down(i);
    }

    // 输出
    while (m--) {
        cout << h[1] << " ";
        del_min();
    }
}
