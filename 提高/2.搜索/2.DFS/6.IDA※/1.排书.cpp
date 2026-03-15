// 搜索过程：
// 书总长为n，1~n
// 枚举移动书目的长度i，长度为i的段共n-i+1个
// 拿出去这i本书后，剩余n-i本书，产生n-i+1个空位；除去原先的位置，剩余n-i个空位
// 但上述有2倍重复，实际上只需要枚举"在自己之后的书"所产生的空位即可
// 枚举这些空位

// 迭代加深+IDA*做法：
// 找启发函数：走到终点的最小步数
// 对于一个有序序列，正确前驱-后继关系应当为n-1个：1-2,2-3,...,n-1-n
// 对于每次移动书目操作，一共会改变3个后继关系
// 我们可以认为这3次改变一定都是正确的(满足了“小于等于性”)
// tot统计所有不正确的后继，每次移动会修复三个；因此启发函数为tot/3上取整
// 考虑到cpp的除法下取整，改写为(tot+2)/3

// 这里还用到了迭代加深的记忆化搜索

#include <algorithm>
#include <cstring>
#include <iostream>


using namespace std;

const int N = 15;

int n;
int q[N];
int w[5][N];    // 用于迭代加深的记忆化搜索

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> q[i];
        }

        int depth = 0;
         
    }
}
