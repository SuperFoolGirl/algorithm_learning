// 给定两个升序的有序数组A,B，以及一个目标值x
// 数组下标从0开始
// 要求求出满足A[i]+B[j]=x的所有(i,j)对的个数
// 只有唯一解

#include <algorithm>
#include <iostream>


using namespace std;

const int N = 100010;

int n, m, x;
int a[N], b[N];

int main() {
    scanf("%d%d%d", &n, &m, &x);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d", &b[i]);
    }

    for (int i = 0, j = m - 1; i < n; i++) {
        while (j >= 0 && a[i] + b[j] > x) {
            j--;
        }
        if (a[i] + b[j] == x) {
            printf("%d %d\n", i, j);
            return 0;
        }
    }
    return 0;
}
