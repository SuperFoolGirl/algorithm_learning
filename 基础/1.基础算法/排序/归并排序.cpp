// 先递归后排序
// 排序时，利用双指针归并
// 分界点：中间值

#include <algorithm>
#include <cstring>
#include <iostream>


using namespace std;

typedef long long LL;

const int N = 100010;
int n;
int q[N], tmp[N];

void merge_sort(int l, int r) {
    if (l >= r) {
        return;
    }

    int mid = (l + r) >> 1;
    merge_sort(l, mid);
    merge_sort(mid + 1, r);

    // 这里合并两个有序数组
    // i为左数组下标起始位置，j为右数组下标起始位置
    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r) {
        if (q[i] <= q[j]) {
            tmp[k++] = q[i++];
        } else {
            tmp[k++] = q[j++];
        }
    }

    // 将左数组剩余的元素放入临时数组
    while (i <= mid) {
        tmp[k++] = q[i++];
    }
    // 将右数组剩余的元素放入临时数组
    while (j <= r) {
        tmp[k++] = q[j++];
    }

    // 将临时数组中的元素拷贝回原数组
    // tmp从下标0开始记录，q作为原数组，本轮合并不一定从0开始
    for (i = l, j = 0; i <= r; ++i, ++j) {
        q[i] = tmp[j];
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> q[i];
    }

    merge_sort(0, n - 1);    // l, r分别为可取到的双边界

    for (int i = 0; i < n; ++i) {
        cout << q[i] << " ";
    }

    return 0;
}
