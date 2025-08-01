// 原版
// 采用两个dfs来实现先输出方案个数再输出方案 有点丑陋 但思路尚可
#include <iostream>
using namespace std;

int n, cnt = 0;
int arr[10] = {0};

void print()
{
    for (int i = 0; i < 10; i++)
        printf("%d ", arr[i]);
    puts("");
}

void dfs_print(int x, int sum)
{
    if (x == 10)
    {
        if (sum == n)
            print();
        return;
    }

    for (int i = 1; i <= 3; i++)
    {
        if (sum + i <= n)
        {
            arr[x] = i;
            dfs_print(x + 1, sum + i);
            arr[x] = 0;
        }
    }
}

void dfs_count(int x, int sum)
{
    if (x == 10)
    {
        if (sum == n)
            cnt++;
        return;
    }

    for (int i = 1; i <= 3; i++)
    {
        if (sum + i <= n)
        {
            arr[x] = i;
            dfs_count(x + 1, sum + i);
            arr[x] = 0;
        }
    }
}

int main()
{
    cin >> n;
    if (n <= 0 || n > 30)
        cout << 0;
    else
    {
        dfs_count(0, 0);
        cout << cnt << endl;
        dfs_print(0, 0);
    }
    return 0;
}


// 改进版
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> solutions; // 存储所有满足条件的方案

void dfs(int x, int sum, int n, vector<int> &arr)
{
    if (x == 10)
    {
        if (sum == n)
            solutions.push_back(arr); // 找到一个满足条件的方案，存储到 solutions 中
        return;
    }

    for (int i = 1; i <= 3; i++)
    {
        if (sum + i <= n)
        {
            arr[x] = i;
            dfs(x + 1, sum + i, n, arr);
            arr[x] = 0; // 回溯
        }
    }
}

int main()
{
    int n;
    cin >> n;

    if (n <= 0 || n > 30)
        cout << 0;
    else
    {
        vector<int> arr(10, 0); // 初始化长度为 10 的数组
        dfs(0, 0, n, arr);

        // 输出方案总数
        cout << solutions.size() << endl;

        // 输出具体方案
        for (const auto &solution : solutions) // 遍历数组或容器
        {
            for (int num : solution)
                cout << num << " ";
            cout << endl;
        }
    }

    return 0;
}