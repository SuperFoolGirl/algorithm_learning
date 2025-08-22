// 以01背包为例，降维后，第二个状态会变为恒等式，代码中需要相应的删除处理

// 下面对原式进行分析：
// f(i,j) = max(f(i-1,j-V[i]) + W[i], f(i-1,j))
// 降维后：
// f(j) = max(f(j-V[i]) + W[i], f(j))

// j原先是从小到达枚举的，也就是说，f(j-V[i])的计算必然会早于f(j)
// 如果j依然从小到大遍历，f(j-V[i])的结果就是本轮的，即f(i,j-V[i])
// 但我们想要的是f(i-1,j-V[i])

// 外层循环i标识着轮数。由于是滚动数组，每进入新的一轮，f(j)的结果都会被覆盖
// 那么，在f(j-V[i])没有被覆盖之前，即等价于原先的f(i-1,j-V[i])，就是我们想要的结果
// 因此，内层j循环改为从大到小，确保计算f(j)时，f(j-V[i])还未被计算，新结果还没将其覆盖，其保存着上一轮的结果

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 1e5 + 10;

int n, m;
int v[N], w[N];
int f[N];    // 降去i这一维

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> v[i] >> w[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= v[i]; j--) {    // 顺序倒置
            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }
    }

    cout << f[m] << endl;
    return 0;
}
