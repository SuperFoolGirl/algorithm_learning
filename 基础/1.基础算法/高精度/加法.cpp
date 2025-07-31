#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 返回的数组是临时变量，不能返回引用
vector<int> add(vector<int> &A, vector<int> &B) {
    vector<int> C;
    int carry = 0;

    // 逐位相加，处理进位
    // 注意这里的循环条件，确保所有位都被处理，必须等到两个加数和进位全部处理完后，才能出循环。这样的处理更简洁
    // 以前的写法需要处理最后可能的进位
    for (int i = 0; i < A.size() || i < B.size() || carry; i++) {
        // 在保证不超过加数位数的情况下，逐位相加
        if (i < A.size()) {
            carry += A[i];
        }
        if (i < B.size()) {
            carry += B[i];
        }
        C.push_back(carry % 10);
        carry /= 10;
    }

    // 在输入合法的情况下，不需要去除前导零
    // 除非输入的数据就有前导零。届时可以在输入处进行处理

    // 结果是逆序的，需要反转
    reverse(C.begin(), C.end());
    return C;
}

int main() {
    string a, b;
    vector<int> A, B;

    // 处理输入，把待计算字符串倒序放入数组
    cin >> a >> b;
    for (int i = a.size() - 1; i >= 0; --i) {
        A.push_back(a[i] - '0');
    }
    for (int i = b.size() - 1; i >= 0; --i) {
        B.push_back(b[i] - '0');
    }

    // 可选：去除前导零
    while (A.size() > 1 && A.back() == 0) {
        A.pop_back();
    }

    while (B.size() > 1 && B.back() == 0) {
        B.pop_back();
    }

    // 核心计算逻辑
    auto c = add(A, B);

    // 输出结果
    for (int i = 0; i < c.size(); ++i) {
        cout << c[i];
    }
    return 0;
}
