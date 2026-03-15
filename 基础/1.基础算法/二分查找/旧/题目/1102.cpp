// 本题有双指针解法

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 200010;
long long n, c, ans = 0;

LL arr[N];

// 蓝色区域的要求
bool check(long long mid, long long x, int opt) {
    if (opt == 0) {
        return mid < x;
    } else {
        return mid <= x;
    }
}

// 这里采用左边为蓝色
int find(long long x, int opt) {
    int l = -1, r = n;
    while (l + 1 < r) {
        int mid = l + r >> 1;
        if (check(arr[mid], x, opt)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    if (opt == 0 && arr[r] == x) {
        return r;
    } else if (opt == 1 && arr[l] == x) {
        return l;
    } else {
        return -1;
    }
}

int main() {
    cin >> n >> c;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    sort(arr, arr + n);
    for (int i = 0; i < n; ++i) {
        long long left = find(arr[i] + c, 0);
        long long right = find(arr[i] + c, 1);
        if (left != -1 && right != -1) {
            ans += right - left + 1;
        }
    }
    cout << ans << endl;
    return 0;
}
