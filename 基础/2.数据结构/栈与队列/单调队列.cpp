// 应用：求滑动窗口的最值
// 滑动窗口每次移动，都会有新的入队和出队

#include <algorithm>
#include <cstring>
#include <iostream>


using namespace std;

const int N = 1e5 + 10;
int n, k;                  // k是滑动窗口的大小
// 这里需要强调一下：q队列里面维护的是a数组的下标，而不是值
int a[N], q[N], hh, tt;    // 队列数组，队头指针，队尾指针

int main() {
    cin >> n >> k;         // 读入序列长度和滑动窗口大小
    for (int i = 0; i < n; i++) {
        cin >> a[i];       // 读入序列
    }

    // 输出滑动窗口的最小值
    int hh = 0, tt = -1;
    for (int i = 0; i < n; i++) {
        // 保持滑动窗口的左端点是不断移动的
        // 注意，并不是每轮都会移动，而是受出队（维护单调）的影响。取决于队首代表的下标
        // 队列里并不会一直包含k个元素
        if (hh <= tt && q[hh] < i - k + 1) {
            hh++;
        }
        // 保持队列单调性，出队
        while (hh <= tt && a[q[tt]] >= a[i]) {
            tt--;
        }
        q[++tt] = i;    // 将当前元素的下标入队。它可能会在下一轮出队

        // 当窗口大小达到k时，输出最小值
        if (i >= k - 1) {
            cout << a[q[hh]] << " ";    // 输出当前窗口的最小值
        }
    }
    cout << endl;                       // 输出换行

    // 输出滑动窗口的最大值
    hh = 0, tt = -1;    // 重置队列
    for (int i = 0; i < n; i++) {
        // 保持滑动窗口的左端点是不断移动的
        if (hh <= tt && q[hh] < i - k + 1) {
            hh++;
        }
        // 保持队列单调性，出队
        while (hh <= tt && a[q[tt]] <= a[i]) {
            tt--;
        }
        q[++tt] = i;    // 将当前元素的下标入队

        // 当窗口大小达到k时，输出最大值
        if (i >= k - 1) {
            cout << a[q[hh]] << " ";    // 输出当前窗口的最大值
        }
    }

    return 0;
}
