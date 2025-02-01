// unordered_multimap有一个问题
// 对于重复键，find(键)返回的是第一个键值对的迭代器
// 无法自由地查找键值对
// 用lower_bound和upper_bound可以进行处理
// 下面展示60分解法
#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
#include <unordered_set>
using namespace std;

// 都是正反两个存 回忆传送门
unordered_multimap<string, string> rule_forward; // 键可能重复 要用multi
unordered_multimap<string, string> rule_backward;
queue<string> q_forward;
queue<string> q_backward;
string A, B;
unordered_multimap<string, int> dist_forward;
unordered_multimap<string, int> dist_backward;
unordered_multimap<string, bool> visited_forward;
unordered_multimap<string, bool> visited_backward;
// 用于遍历哈希表 当然也可以用for循环迭代器
unordered_multiset<string> keys_forward;
unordered_multiset<string> keys_backward;

int bfs()
{
    if (A == B)
        return 0;

    dist_forward.insert({A, 0}); // 不支持下标索引
    dist_backward.insert({B, 0});
    visited_forward.insert({A, true});
    visited_backward.insert({B, true});
    q_forward.push(A);
    q_backward.push(B);

    while (!q_forward.empty() || !q_backward.empty())
    {
        if (!q_forward.empty()) // 不加报错
        {
            auto t_forward = q_forward.front();
            q_forward.pop();
            string copy_forward = t_forward;

            for (auto const &key : keys_forward)
            {
                t_forward = copy_forward;
                // 这是string类的find，用于查找子串
                auto pos = t_forward.find(key); // find这里返回一个指向键值对的迭代器，因此下面要取second
                if (pos != string::npos)
                {
                    int len = key.length();
                    string new_key = t_forward.replace(pos, len, rule_forward.find(key)->second);

                    if (!visited_forward.find(new_key)->second) // find返回一个指向键值对的迭代器
                    {
                        dist_forward.find(new_key)->second = dist_forward.find(copy_forward)->second + 1; // t已经改了 这里要用copy
                        visited_forward.find(new_key)->second = true;
                        q_forward.push(new_key);

                        // 在查重中检查相遇
                        if (visited_backward.find(new_key)->second)
                            return dist_forward.find(new_key)->second + dist_backward.find(new_key)->second;
                    }
                    // 不能break。因为A中可能服从多个rule
                    // 因此要恢复t_forward replace会直接修改t_forward
                }
            }
        }

        if (!q_backward.empty())
        {
            auto t_backward = q_backward.front();
            q_backward.pop();
            string copy_backward = t_backward;

            for (auto const &key : keys_backward)
            {
                t_backward = copy_backward;
                auto pos = t_backward.find(key);
                if (pos != string::npos)
                {
                    int len = key.length();
                    string new_key = t_backward.replace(pos, len, rule_backward.find(key)->second);

                    if (!visited_backward.find(new_key)->second)
                    {
                        dist_backward.find(new_key)->second = dist_backward.find(copy_backward)->second + 1;
                        visited_backward.find(new_key)->second = true;
                        q_backward.push(new_key);

                        if (visited_forward.find(new_key)->second)
                            return dist_forward.find(new_key)->second + dist_backward.find(new_key)->second;
                    }
                }
            }
        }
    }
    return -1;
}

int main()
{
    cin >> A >> B;
    string a, b;
    while (cin >> a >> b)
    {
        rule_forward.insert({a, b});
        rule_backward.insert({b, a});
        keys_forward.insert(a);
        keys_backward.insert(b);
    }
    int ret = bfs();

    if (ret >= 1 && ret <= 10)
        cout << ret;
    else
        cout << "NO ANSWER!";
    return 0;
}