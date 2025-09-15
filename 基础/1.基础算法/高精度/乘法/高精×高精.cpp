#include <iostream>
#include <vector>

using namespace std;

vector<int> mul(vector<int> &A, vector<int> &B) {
    // 结果最多是 A.size() + B.size() 位，所以需要 A.size() + B.size() 的空间来存储结果（不含最终进位）
    // 初始大小为 A.size() + B.size() 是为了有足够的空间容纳所有累加的乘积
    vector<int> c(A.size() + B.size(), 0);

    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < B.size(); j++) {
            c[i + j] += A[i] * B[j];
        }
    }

    // 统一处理进位
    int t = 0;
    // 结果的实际长度可能小于 lena + lenb，需要根据进位来确定
    // 最大的可能长度是 lena + lenb
    for (int i = 0; i < c.size(); i++) {
        int sum = c[i] + t;    // 当前位加上上一位的进位
        c[i] = sum % 10;       // 当前位的值
        t = sum / 10;          // 计算新的进位
    }

    // 如果最后还有进位，则添加到c的末尾
    if (t > 0) {
        c.push_back(t);
    }

    // 去除前导零（虽然对于乘法，除非是0*0，否则不太可能出现实际的前导零）
    // 但保留这个逻辑是为了通用性，或者处理0*0的情况
    while (c.size() > 1 && c.back() == 0) {
        c.pop_back();
    }

    return c;
}

int main() {
    string a, b;
    vector<int> A, B;
    cin >> a >> b;

    for (int i = a.size() - 1; i >= 0; i--) {
        A.push_back(a[i] - '0');
    }

    for (int i = b.size() - 1; i >= 0; i--) {
        B.push_back(b[i] - '0');
    }

    vector<int> res = mul(A, B);

    for (int i = res.size() - 1; i >= 0; i--) {
        cout << res[i];
    }

    return 0;
}
