// 先排序再递归

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 100010;
int n;
int q[N];

// 这个写法边界条件很严格，如果需要的话考虑直接背过
// 那我为什么不用sort呢

void quick_sort(int l, int r) {
    if (l >= r) {
        return;
    }

    int x = q[l], i = l - 1, j = r + 1;
    while (i < j) {
        // 这里必须写成do while，因为每次新循环都要无条件走一步
        // 如果用while的话，可能会卡死

        // 找到左边大于等于 x 的位置
        do {
            i++;
        } while (q[i] < x);
        // 找到右边小于等于 x 的位置
        do {
            j--;
        } while (q[j] > x);
        // 交换这两个位置的元素
        if (i < j) {
            swap(q[i], q[j]);
        }
    }
    // j是中间分隔点

    quick_sort(l, j);
    quick_sort(j + 1, r);
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> q[i];
    }

    quick_sort(0, n - 1);

    for (int i = 0; i < n; ++i) {
        cout << q[i] << " ";
    }

    return 0;
}