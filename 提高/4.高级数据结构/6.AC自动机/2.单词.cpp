// 一个字符串s出现的次数，等于：
// 满足要求的所有前缀的个数
// 要求是：前缀本身的后缀中有s
// 举个例子：
// xxxxxababaxxxxx
// 请问在以上文本串(单个单词)中，s="aba"出现了几次？
// 满足要求的前缀有两个：xxxxxaba、xxxxxababa
// 他们的后缀都可以是s="aba"，因此s出现了两次

// 之所以这样定义，是为了更好地符合Trie图
// 当然，并不是正向算——对于每一个要检查的s，检查所有前缀的后缀是否有s
// 而是，对于每个遍历到的前缀，检查它的所有后缀，能和哪些前缀匹配
// 进而可以用递推的思想，因为是拓扑序：不断嵌套ne数组，直到无法继续为止
// 所有的i连一条边到ne[i]，绝对是DAG
// 这个过程中，所以答案都会求到，我们从中取自己需要查找的s就好了

// f[i]表示单词i出现的次数
// 则有f[i]应当累加到f[ne[i]]上，因为i的后缀是ne[i]，所以i出现了多少次，ne[i]也就出现了多少次
// 就这样，不断连成一个DAG

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1000010;

int n;
int tr[N][26], idx;
int q[N], ne[N];
int f[N];
char str[N];
int id[210];  // 记录每个单词对应的下标

void insert(int x) {
    int p = 0;
    for (int i = 0; str[i]; i++) {
        int t = str[i] - 'a';
        if (!tr[p][t]) {
            tr[p][t] = ++idx;
        }
        p = tr[p][t];
        // 本题f可取代cnt，同时对于每个结点都需要记录，而不只是记录单词结点
        f[p]++;
    }
    id[x] = p;
}

void build() {
    int hh = 0, tt = -1;
    for (int i = 0; i < 26; i++) {
        if (tr[0][i]) {
            q[++tt] = tr[0][i];
        }
    }

    while (hh <= tt) {
        int t = q[hh++];
        for (int i = 0; i < 26; i++) {
            int p = tr[t][i];
            if (!p) {
                tr[t][i] = tr[ne[t]][i];
            } else {
                ne[p] = tr[ne[t]][i];
                q[++tt] = p;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> str;
        insert(i);
    }

    build();

    // q中放着逆拓扑序
    for (int i = idx - 1; i >= 0; i--) {
        f[ne[q[i]]] += f[q[i]];
    }

    for (int i = 0; i < n; i++) {
        cout << f[id[i]] << "\n";
    }

    return 0;
}
