#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string p, s;
    cin >> p >> s;         // 使用C++ string，下标默认从0开始

    int n = p.length();    // 模式串p的长度
    int m = s.length();    // 主串s的长度

    // ne数组用来存储最长相等前缀和后缀的长度
    // ne[i]表示p[0...i]这个子串的最长相等前后缀长度
    // ne[0] = 0，因为单个字符没有前后缀
    vector<int> ne(n, 0);

    // 计算next数组，统计模式串p的前缀信息
    for (int i = 1, j = 0; i < n; i++) {
        // 当p[i]和p[j]不匹配时，如果j不是在开头，那么j回溯
        // 循环中，i是不断往前走的，j是不断往回走的
        // 这句回溯代码值得细细讲解，后面也频繁出现
        // 巧妙的是，next数组本身的求法，也是利用了kmp思想，毕竟前后缀也是需要匹配的

        // p[j]与p[i]不匹配了，但从p[0]到p[j-1]是匹配的。这段匹配了的串，去找它前后缀相等的部分
        // 所以这里ne[j-1]的含义就是，p[0]到p[j-1]这段子串最大的前后缀相等的长度。设这个前后缀为k
        // 那么j跳转到的下标是k的下一位。因为k肯定能与p[i-1]及之前的内容匹配上，所以用k的下一位与p[i]进行匹配
        // 还是把两个串上下放在一起比较看起来直观

        // 下面来模拟该串next数组不为0的所有情况
        // p: ABCABABC

        // i=3,j=0,ne[3]=1
        // ABC-A-BABC
        //    -A-BCABABC

        // i=4,j=1,ne[4]=2
        // ABC-AB-ABC
        //    -AB-CABABC

        // 下一步，A与C不再匹配，j跳转到ne[1]
        // 也就是说，AB是已经匹配好的串了，不过这个串没有相同前后缀，所以j要跳到0了，从头开始

        // i=5,j=0,ne[5]=1
        // ABCAB-A-BC
        //      -A-BCABABC

        // i=6,j=1,ne[6]=2
        // ABCAB-AB-C
        //      -AB-CABABC

        // i=7,j=2,ne[7]=3
        // ABCAB-ABC-
        //      -ABC-ABABC
        while (j > 0 && p[i] != p[j]) {
            j = ne[j - 1];
        }
        // 当p[i]和p[j]匹配时，j前进
        if (p[i] == p[j]) {
            j++;
        }
        // 此时j的值就是前缀的长度，i正处于后缀的最后一个字符的下标
        ne[i] = j;
    }

    // KMP匹配过程，外层遍历主串s，内层遍历模式串p
    for (int i = 0, j = 0; i < m; i++) {
        // 当s[i]和p[j]不匹配时，j回溯
        while (j > 0 && s[i] != p[j]) {
            j = ne[j - 1];
        }
        // 当s[i]和p[j]匹配时，j前进
        if (s[i] == p[j]) {
            j++;
        }

        // 如果j等于模式串的长度n，说明找到一个完整匹配
        if (j == n) {
            // 输出匹配的起始位置（s的下标）
            cout << i - n + 1 << " ";
            // 继续寻找下一个匹配，j回溯
            j = ne[j - 1];
        }
    }
    cout << endl;

    return 0;
}
