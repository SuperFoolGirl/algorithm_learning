// 题目给定升序（不严格递增）的序列，可能会出现多个重复元素
// 例：1 2 2 3 5，显然答案是3

#include <algorithm>
#include <iostream>


using namespace std;

const int N = 100010;

int n;
int q[N];
int cnt[N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &q[i]);
    }

    // i,j作为同侧双指针
    int res = 1;
    for (int i = 1, j = 1; i <= n; i++) {
        cnt[q[i]]++;
        // 当出现重复元素时，会不断移动j，直到i和j指向同一位置
        // 期间i-j中间的元素出现次数要做自减处理
        while (cnt[q[i]] > 1) {
            cnt[q[j]]--;
            j++;
        }
        res = max(res, i - j + 1);
    }
    printf("%d", res);
    return 0;
}
