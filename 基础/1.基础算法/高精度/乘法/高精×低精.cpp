#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// 用A的每一位与B相乘，而不是B的每一位
// 如果是高精度×高精度的话，就需要逐位相乘再相加了
// 这里把B看成一个整体
vector<int> mul(vector<int> &A, int b) {
    vector<int> C;
    int carry = 0;

    // 逐位相乘，处理进位
    for (int i = 0; i < A.size() || carry; i++) {
        if (i < A.size()) {
            carry += A[i] * b;
        }
        C.push_back(carry % 10);
        carry /= 10;
    }

    return C;
}

int main() {
    // 高精度 × 整数
    string a;
    int b;
    vector<int> A;
    cin >> a >> b;

    for (int i = a.size() - 1; i >= 0; --i) {
        A.push_back(a[i] - '0');
    }

    auto C = mul(A, b);

    for (int i = C.size() - 1; i >= 0; --i) {
        cout << C[i];
    }

    return 0;
}