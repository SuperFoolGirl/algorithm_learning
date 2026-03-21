// 离散化标志：数据范围极大，空间复杂度无法承受
// 本题涉及两个操作：在某个位置c上加数x、求区间和[l,r]
// 这两个操作都需要离散化：找到c,l,r在离散化后的坐标，进而完成对应操作
// 找坐标：把所有需要用到的c,l,r放到一个数组中，排序去重后，将新数组的下标作为离散化后的坐标(从0开始)
// 要找到原数据到新离散化坐标的映射，可以选择二分或哈希；二分效率要高于map

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 300010;  // 需要离散化的数的个数

int n, m;
// a用于存离散化进行的数值操作
// 举个例子，设t为原数据，find(t)返回t在离散化后的坐标x，那么对原数据t的增改就可以在a[x]上进行
int a[N];
int s[N];  // s存储前缀和
// add和query存在的意义是，离散化必须先读入所有数据，因此需要先把数据存储起来
vector<PII> add, query;    // 存储加数和查询区间
vector<int> alls;  // 离散化坐标与原数据的映射

int find(int x) {
    // x是原数据，要返回其离散化后的坐标
    // 这里用哪个模板都行，毕竟x一定唯一存在。这里选右模板了
    int l = 0, r = alls.size() - 1;
    while (l < r) {
        int mid = l + r >> 1;
        if (alls[mid] >= x) {  // 找到的mid处于目标的右区间
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    // 注意，本题离散化坐标要映射到从1开始
    // 因为本题要求区间和，需要用到前缀和
    return r + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    // 离散化算法需要先读入所有需要离散化的数据
    cin >> n >> m;
    // 读入加数操作
    for (int i = 0; i < n; i++) {
        int x, c;  // x是位置，c是加数
        cin >> x >> c;
        add.push_back({x, c});
        alls.push_back(x);  // 显然只有x需要离散化
    }
    // 读入查询区间和操作
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        query.push_back({l, r});
        alls.push_back(l);
        alls.push_back(r);
    }

    // alls去重
    sort(alls.begin(), alls.end());
    alls.erase(unique(alls.begin(), alls.end()), alls.end());

    // 已完成离散化，下面进行加数和查询区间和的操作

    // 加数操作
    for (auto item : add) {
        int x = find(item.first);
        a[x] += item.second;
    }

    // 预处理前缀和
    // alls存储了所有的操作数，除了x还有l、r
    // 如果x不和lr重复的话，那么所有的l、r对应的a[]应该是0
    // 在这种情况下，前缀和其实也是合理的：
    // 完全可以当l、r有一个为0的加数，不会影响前缀和的正确性
    // 又因为x,l,r都是排序的，因此前缀和的计算也是合理的
    for (int i = 1; i <= alls.size(); i++) {
        s[i] = s[i - 1] + a[i];
    }

    // 处理询问
    for (auto item : query) {
        int l = find(item.first);
        int r = find(item.second);
        cout << s[r] - s[l - 1] << endl;
    }

    return 0;
}
