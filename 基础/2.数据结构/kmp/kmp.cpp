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
    for (int i = 1, j = 0; i < n; i++) {    // 注意i从1开始
        // 当p[i]和p[j]不匹配时，如果j不是在开头，那么j回溯
        // 循环中，i是不断往前走的，j是不断往回走的
        // 这句回溯代码值得细细讲解，后面也频繁出现
        // 巧妙的是，next数组本身的求法，也是利用了kmp思想，毕竟前后缀也是需要匹配的

        // p[j]与p[i]不匹配了，但从p[0]到p[j-1]是匹配的。这段匹配了的串，去找它前后缀相等的部分
        // 所以这里ne[j-1]的含义就是，p[0]到p[j-1]这段子串最大的前后缀相等的长度。设前面为xxoxx，则相同前后缀为xx，ne[j-1] = 2
        // 因为p[j] != p[i]，因此把p中前面的xx与后面的xx对上，如下图所示
        // 原本：xxoxxy    跳转：xxoxxy
        //      xxoxxz            xxoxxz
        // 给j赋值ne[j-1]，而j本身要作为下标，因此下一个要重新匹配的起始元素p[j]，其实恰好就是重叠前后缀的下一位，用 p[j] = o 来和 p[i] = y 来进行比较
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
        // j所记录的下标，对于串来说，总是从第一个字符开始的。最后j又会恰好指向下一个待比较的元素，所以可以直接赋值给ne[i]
        ne[i] = j;
    }

    // KMP匹配过程，外层遍历主串s，内层遍历模式串p
    for (int i = 0, j = 0; i < m; i++) {    // i从0开始，与ne数组不同
        // 当s[i]和p[j]不匹配时，j回溯
        while (j > 0 && s[i] != p[j]) {
            j = ne[j - 1];
        }
        // 当s[i]和p[j]匹配时，j前进
        if (s[i] == p[j]) {
            j++;
        }

        // 如果j等于模式串的长度n，说明找到一个完整匹配
        // 上面找ne数组的时候也说了，对于模式串而言，j的偏移量是相对于串的第一个字符的，所以可以拿过来直接用
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
