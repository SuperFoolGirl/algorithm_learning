#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int find(vector<int> &arr, int x, int n) {
    int l = -1, r = n;
    while (l + 1 < r) {
        int mid = l + r >> 1;
        if (arr[mid] < x) {
            l = mid;
        } else {
            r = mid;
        }
    }
    if (arr[r] == x) {
        return r + 1;
    }
    return -1;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<int> arr(n, 0);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    while (m--) {
        int x;
        scanf("%d", &x);
        printf("%d ", find(arr, x, n));
    }
    return 0;
}
