// 类似食物链

// N最大为1e9，可以断定要用离散化了

// 借用前缀和的思想
// 前缀和Si表示前i个数中1的个数
// 若有题设“[l,r]中共有奇数个1”，则有S[r]-S[l-1]为奇数
// 进而意味着S[r]和S[l-1]的奇偶性不同(奇偶性相同则和差均为偶数)
// 不过本题并不需要去真正构建前缀和数组，只是需要狐假虎威地借用这个思想

// 因此，每次询问，等于告诉我们“两个数的奇偶性是否相同”，数指S[i]
// 那么如何用带权并查集来做呢？
// d[x]表示x与p[x]的关系，0表示同类，1表示不同类
// 如果x和y处于同一集合
// 则若d[x]+d[y]为偶数，则x和y同类；若d[x]+d[y]为奇数，则x和y不同类(和/差皆可)
// 以奇数情况为例。不妨设d[x]=0，则x和root同类；那么必然有d[y]=1，y和root不同类，因此x和y不同类
// 只需要知道每个点和根的关系，就能知道集合内任意两点的关系了——这就是选择带权并查集的根本所在

// 使用并查集，应当满足的关系为：传递性、对称性

// 具体操作
// 1.x与y是同一类
// 1.1 若px==py，则判断是否有矛盾即可：d[x]^d[y]=1则有矛盾
// 1.2 若px!=py，则合并x至y，令p[px]=py。此时d[px]可视为连向py的边的权值，应当满足d[x]+d[px]+d[y]是偶数，才能使得x和y同类。
//     即d[px]=-d[x]-d[y]。由于本题是模2域，转为d[px]=d[x]+d[y]。又因为模2域下加法等价于异或(不进位加法)，因此d[px]=d[x]^d[y]
// 2.x与y是不同类
// 2.1 若px==py，则判断是否有矛盾即可：d[x]^d[y]=0则有矛盾
// 2.2 若px!=py，则应有d[px]=d[x]^d[y]^1，我们需要让d[x]+d[px]+d[y]是奇数，才能使得x和y不同类

#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_map>

using namespace std;

const int N = 20010;

int n, m;
int p[N], d[N];
unordered_map<int, int> S;  // 本题可以无需离线离散化，不用把数据预先存好，因为不需要排序二分

int get(int x) {
    if (!S.count(x)) {
        S[x] = ++n;
    }
    return S[x];
}

int find(int x) {
    if (p[x] != x) {
        int root = find(p[x]);
        d[x] ^= d[p[x]];  // 模2域下加法等价于异或
        p[x] = root;
    }
    return p[x];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 读入n无意义，我们要离散化的。下面直接给0
    cin >> n >> m;
    n = 0;

    for (int i = 0; i < N; i++) {
        p[i] = i;
    }

    int res = m;  // 若整个数据无矛盾，则答案应该是m
    for (int i = 1; i <= m; i++) {
        int a, b;
        string type;
        cin >> a >> b >> type;
        // 前缀和思想在这里，S[a-1]和S[b]的关系即为a和b的关系
        a = get(a - 1), b = get(b);

        int t = 0;
        if (type == "odd") {
            t = 1;
        }

        int pa = find(a), pb = find(b);
        if (pa == pb) {
            if ((d[a] ^ d[b]) != t) {  // 有矛盾
                res = i  -1;
                break;
            } else {
                p[pa] = pb;
                d[pa] = d[a] ^ d[b] ^ t;  // 此处d[pa]的更新不依赖sz，而是由题目推导来的
            }
        }
    }

    cout << res << "\n";

    return 0;
}
