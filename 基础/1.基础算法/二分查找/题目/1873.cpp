#include <cstdio>
#include <vector>
using namespace std;

// 讲一下check函数的逻辑
// 如果mid处于蓝色区域内，那check会返回真，表示mid高度可以满足要求，所以可以进一步缩小蓝色区域的边界，找到更好的解
// 如果mid处于蓝色区域外，那check会返回假，表示mid高度不满足要求，所以需要扩大蓝色区域的边界
bool check(int x, vector<int> &trees, int n, int m) {
    int len = 0;
    for (auto i : trees) {
        if (i > x) {
            len += i - x;
        }
        // 这里加上一个判断，如果砍到的木材长度大于等于m，直接返回真
        // 一方面是节约时间，一方面是防止爆int
        if (len >= m) {
            return true;
        }
    }
    // 如果砍到的木材长度大于等于m，说明这个高度可以满足要求，返回真
    return len >= m;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<int> trees(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &trees[i]);
    }

    // 第一次做二分查找结合具体情境的题目，我们要找到查找的对象，这个直接从题目里读即可
    // 查找的值为锯片高度
    // 锯片高度越低，砍到的木材越多
    // 我们要满足砍到足够的木材，所以蓝色区域在左边
    // 注意l的设定，锯片最小为1，因此设l为0
    int l = 0, r = 400001;
    while (l + 1 < r) {
        int mid = l + r >> 1;
        if (check(mid, trees, n, m)) {
            l = mid;
        } else {
            r = mid;
        }
    }

    // 根据check的条件，当len=m时，也算在蓝色区域
    // 因此我们取蓝色区域的上界，即l
    // 但要注意有些数据会卡人，所以这里左右边界都判断一下
    // 理想中，r是不满足条件的；但如果check(r)是真的，说明r也是满足条件的
    if (check(r, trees, n, m)) {
        printf("%d\n", r);
    } else {
        printf("%d\n", l);
    }
    return 0;
}
