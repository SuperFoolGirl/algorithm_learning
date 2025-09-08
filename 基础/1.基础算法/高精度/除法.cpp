#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> div(vector<int> &A, int b, int &r) {
    vector<int> C;
    r = 0;

    // 除法在逻辑上是从高位到低位进行的
    // 但加减乘中，数组都是倒序存储的
    // 这里为了延续前面的习惯，注意一下顺序
    for (int i = A.size() - 1; i >= 0; --i) {
        r = r * 10 + A[i];     // 逐位构建被除数
        C.push_back(r / b);    // 商
        r %= b;                // 更新余数
    }
    // 反转商
    reverse(C.begin(), C.end());
    // 去除前导零
    while (C.size() > 1 && C.back() == 0) {
        C.pop_back();
    }
    return C;
}

int main() {
    // 高精度 / 整数
    string a;
    int b;
    vector<int> A;
    cin >> a >> b;

    for (int i = a.size() - 1; i >= 0; --i) {
        A.push_back(a[i] - '0');
    }

    int r;    // 余数
    auto C = div(A, b, r);

    // 输出商和余数
    for (int i = C.size() - 1; i >= 0; --i) {
        cout << C[i];
    }
    cout << endl << r;

    return 0;
}
