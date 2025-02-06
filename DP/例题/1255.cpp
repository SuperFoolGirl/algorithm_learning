// 本题展示了记忆化搜索
// 不过需要用到高精度才能拿满分 这里先略过了

#include <iostream>

int n;
int ans = 0;
int mem[6000] = {0};

int dfs(int x)
{
    if (mem[x]) // 记忆化搜索
        return mem[x];

    int sum = 0;
    if (x == 1)
        sum = 1; // 这里不要直接return 后面要执行记忆化，存储完后返回
    else if (x == 2)
        sum = 2;
    else
        sum = dfs(x - 1) + dfs(x - 2);

    mem[x] = sum; // 记忆化
    return sum;   // 回忆非void函数的递归返回值
}

int main()
{
    std::cin >> n;
    std::cout << dfs(n);
    return 0;
}