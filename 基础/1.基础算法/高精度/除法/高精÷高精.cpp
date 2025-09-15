// 基于减法的原理来实现除法

#include <iostream>
#include <vector>

using namespace std;

bool check(vector<int> &A, vector<int> &B, int a) {          // 判断len长度的 b 是否可以被 a 除
    if (A.size() > a + B.size() && A[a + B.size()] > 0) {    // 避免越界访问
        return true;                                         // 如果 a 比 b 长, 一定可以除
    }
    for (int i = B.size() - 1; i >= 0; i--) {                // 从 a 的最高位开始比
        // 注意，a[i] == b[i] 的情况要继续比下去，无法立刻判断出来大小
        if (A[a + i] > B[i]) {
            return true;     // 除去相等位的最高位大于b,说明a比b大,可以除
        } else if (A[a + i] < B[i]) {
            return false;    // 除去相等位的最高位小于b,说明a比b小，不可以除
        }
    }
    return true;             // a和b完全一样,可以除
}

vector<int> div(vector<int> &A, vector<int> &B) {
    vector<int> C(A.size() - B.size() + 1, 0);    // 商的最大长度为 被除数长度-除数长度+1

    for (int i = A.size() - B.size(); i >= 0; i--) {
        // data()函数返回vector的首地址，使得可以像操作C风格数组一样操作vector
        // 获取 vector<int> A 中从第 i 个元素开始的连续内存区域的指针
        while (check(A, B, i)) {                         // 当A可以被B减的时候一直进行，直到不能被减,即得到最终的商
            C[i]++;                                      // 记录A被B减的次数，即为除法的结果
            for (int j = 0; j <= B.size() - 1; j++) {    // 高精度减法的实现方法，从低位减到高位
                if (A[i + j] < B[j]) {
                    A[i + j + 1]--;                      // 借位
                    A[i + j] += 10;
                }
                A[i + j] -= B[j];
            }
        }
    }

    // A此时就是余数
    while (A.size() > 1 && A.back() == 0) {
        A.pop_back();    // 去掉前缀无用的零
    }
    while (C.size() > 1 && C.back() == 0) {
        C.pop_back();
    }

    return C;
}

int main() {
    // 只能处理 正数÷正数
    string a, b;
    vector<int> A, B, C;
    cin >> a >> b;

    // 两个特判
    if (b == "0") {    // 除数不能为0
        return 0;
    }
    if (b.size() > a.size() || (b.size() == a.size() && b > a)) {
        cout << "0" << endl;    // 被除数短于除数，商为0，余数为被除数
        cout << a << endl;
        return 0;
    }

    for (int i = a.size() - 1; i >= 0; i--) {
        A.push_back(a[i] - '0');    // 字符型转int型
    }
    for (int i = b.size() - 1; i >= 0; i--) {
        B.push_back(b[i] - '0');
    }

    C = div(A, B);

    // 输出商和余数
    for (int i = C.size() - 1; i >= 0; --i) {
        cout << C[i];
    }
    cout << endl;
    for (int i = A.size() - 1; i >= 0; --i) {
        cout << A[i];
    }

    return 0;
}
