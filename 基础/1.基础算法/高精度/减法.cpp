#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 判断AB大小
bool cmp(vector<int> &A, vector<int> &B) {
    if (A.size() != B.size()) {
        return A.size() > B.size();
    }

    // 此时A和B长度相同
    // 数组从低到高存的是个位到高位
    // 比较大小，要从高位到低位去比
    for (int i = A.size() - 1; i >= 0; --i) {
        if (A[i] != B[i]) {
            return A[i] > B[i];
        }
    }

    return true; // 相等的情况
}

vector<int> sub(vector<int> &A, vector<int> &B) {
    vector<int> C;
    int borrow = 0;

    // 逐位相减，处理借位
    for (int i = 0; i < A.size(); i++) {
        int a = A[i] - borrow;
        int b = (i < B.size()) ? B[i] : 0;

        if (a < b) {
            a += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        C.push_back(a - b);
    }

    // 去前导0
    while (C.size() > 1 && C.back() == 0) {
        C.pop_back();
    }

    return C;
}

int main() {
    // 输入假定都为正整数
    // 如果存在负数情况，可以通过前置的一些数学方法，将减法转换为加法，或者将加法转换为减法
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

    // 下面的cmp函数依赖于输入的合法性，即不允许有前导零
    // 假设为正确输入。如果未处理前导零，参考加法
    // 如果A大于B，直接输出A-B，否则输出B-A并加上负号
    if (cmp(A, B)) {
        auto C = sub(A, B);
        for (int i = C.size() - 1; i >= 0; --i) {
            cout << C[i];
        }
    } else {
        auto C = sub(B, A);
        cout << '-';
        for (int i = C.size() - 1; i >= 0; --i) {
            cout << C[i];
        }
    }
    
    return 0;
}
