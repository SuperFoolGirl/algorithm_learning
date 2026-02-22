// 给定整数a, b，求a和b之间的所有数字中0~9出现的次数
// 例如a=1024，b=1032
// a与b之间的9个数为1024, 1025, 1026, 1027, 1028, 1029, 1030, 1031, 1032
// 其中0出现了10次，1出现了10次，2出现了7次，3出现了3次...

// 思路：
// 如果一个区间的答案不好求，那就将其转为求前缀的答案
// 这是一种通用的思路，与前缀和类似
// 实现函数count(n, x)，用于计算1~n中数字x出现的次数
// 那么a和b之间数字x出现的次数就等于count(b, x) - count(a-1, x)

// 对于不同的x，求法有差异。分成0和1~9两种情况来讨论
// 设n为7位abcdefg，研究从1~n中数字x出现的次数

// 一、x取1~9
// 以求x=1在第4位(从左到右)出现的次数为例，研究数字xxx1yyy
// 对于1 <= xxx1yyy <= abcdefg，分析前三位xxx的取法
// 情况1. 000 <= xxx <= abc-1
// 此时y可以取遍000~999，1出现的次数为1000*abc（只算第4位，别的位出现1不关注）
// 1000是因为y有1000种取法：000~999；abc是因为xxx有abc种取法：000~abc-1
// 情况2. xxx = abc，研究数字记为abc1yyy
// (1) d < 1，则abc1yyy > abcdefg，超出上限，不在讨论范围内
// (2) d = 1，则y可以取000~efg，第四位1出现的次数为efg + 1
// (3) d > 1，则y可以取000~999，第四位1出现的次数为1000（同上，1000-1999中，第四位的1共出现1000次）

// 二、x取0
// 类似地，研究数字xxx0yyy
// 当x取0时，不允许有前导0。如数字0000123，实际上是123，这个数字中没有出现过0
// 考虑左高位xxx的取法。若0位于最高位，没有左高位，0yyyyyyy是不合法数字
// 想想也知道，哪有最高位是0的数字？因此，至少是x0yyyyy
// 情况1. 000 <= xxx <= abc-1
// 因此，对于第四位x取0的情况，左高位应该从1开始取，即001，范围是001~abc-1
// 情况2. xxx = abc，研究数字记为abc0yyy
// 与上面相同。

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>


using namespace std;

const int N = 1e5 + 10;

int get(vector<int>& num, int l, int r) {
    int res = 0;
    for (int i = l; i >= r; i--) {
        res = res * 10 + num[i];
    }
    return res;
}

int power10(int x) {
    int res = 1;
    while (x--) {
        res *= 10;
    }
    return res;
}

// count(n, x)表示1~n中数字x出现的次数
int count(int n, int x) {
    if (!n) {
        return 0;
    }

    // 拆分出n的每一位
    vector<int> num;
    while (n) {
        num.push_back(n % 10);
        n /= 10;
    }

    // 将n置为其位数
    n = num.size();

    int res = 0;
    // 从最高位开始枚举每一位，研究该位上x出现的次数
    // 当取最高位时，又有以下问题
    // x取0时，情况1和情况2都不存在
    // x取非0时，情况1不存在(没有左高位)，情况2存在
    for (int i = n - 1 - !x; i >= 0; i--) {
        if (i < n - 1) {  // 最高位时，无论如何情况1都不存在
            // 情况1
            res += get(num, n - 1, i + 1) * power10(i);    // abc*1000
            if (!x) {
                // 当x取0时，左高位应该从1开始取，即001，范围是001~abc-1
                // 相比上面，减去一次即可
                res -= power10(i);
            }
        }
        // 情况2
        // ① d < x (舍弃)
        if (num[i] == x) {                    // ② d = x
            res += get(num, i - 1, 0) + 1;    // efg + 1
        } else if (num[i] > x) {              // ③ d > x
            res += power10(i);                // 1000
        }
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int a, b;
    while (cin >> a >> b, a || b) {
        if (a > b) {
            // 使得a小于b，方便后续计算
            swap(a, b);
        }

        // 计算0~9在范围内出现的次数
        for (int i = 0; i < 10; i++) {
            cout << count(b, i) - count(a - 1, i) << ' ';
        }
        cout << endl;
    }

    return 0;
}
