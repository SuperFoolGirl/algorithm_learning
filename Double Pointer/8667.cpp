// 有二分做法

#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int N = 100010;

int n;
int a[N], b[N], c[N];

int main()
{
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &b[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &c[i]);

    sort(a, a + n);
    sort(b, b + n);
    sort(c, c + n);

    ll res = 0;
    for (int i = 0, idxA = 0, idxC = 0; i < n; i++)
    {
        int B = b[i];
        // 出循环时，idxA会落在第一个大于等于B的元素上，相当于落在二分的r上了（左边是蓝色）
        while (idxA < n && a[idxA] < B) // <
            idxA++;
        // 出循环时，idxC会落在第一个大于B的元素上，相当于落在二分的r上了（右边是蓝色）
        while (idxC < n && c[idxC] <= B) // <=
            idxC++;
        res += (ll)idxA * (n - idxC);
    }
    printf("%lld", res);
    return 0;
}