import os
import sys
from collections import deque

# 请在此输入您的代码
# 没有上司的舞会，状态机
# f(u,0)表示在以u为根的子树中选，且不选u的最优方案
# f(u,1)表示在以u为根的子树中选，且选u的最优方案
# u不选时，其子结点可选可不选
# f(u,0) = sum(max(f(v1,0),f(v1,1)), ...)
# 若选u，子结点不可选
# f(u,1) = w[u]+sum(f(v1,0),f(v2,0)...)

# 另一个条件：与树根距离不相同
# 也就是说，一层节点只能选一个
# 因此，需要更改一部分逻辑
# 这里指出一个错误想法：把sum全改成max不能实现目标
# 这样会导致，最终只会选择点权最大的一个点
# 那么，如何考虑“每层只选一个呢”？
# 首先，预处理深度
# 其他树形DP都是自底向上的，但本题需要自顶向下考虑
# 每层选一个，第i-1层已选出最大值
# 考虑i层时，假设要选结点u，则需要判断i-1层最大值是否来源于u的父亲；如果是，则i-1层应当取次大值(必定不来自u的父亲)
# 因此，直接按层遍历即可，不需要递归
# f数组定义修改为自顶向下的：
# f[u][0/1]表示从根结点到u结点这些层中，不选/选u的属性

# 这个题可以这样来看：
# 对于普通线性DP，可以视为“每层只有一个点”
# 但对于本题，拓扑序在层与层之间，点之间是并列关系
# 要遍历这些并列的点，提炼出这一层的属性，用这一层来更新下一层
# 维护i-1层的属性，本题用了max123三个数组，分别维护“在i-1层选点时的最大值”“在i-1层选点时的次大值”“不在i-1层选点时的最大值”
# 状态转移方程略复杂，这里不多说，详见代码


def solve():
    it = iter(sys.stdin.read().split())
    ri = lambda: int(next(it))

    n = ri()
    fa = [0, 0] + [ri() for _ in range(n - 1)]
    w = [0] + [ri() for _ in range(n)]
    f = [[0] * 2 for _ in range(n + 1)]
    depth = [0] * (n + 1)
    deepest = 0
    h = [[] for _ in range(n + 1)]

    # 为了求depth，需要邻接表
    for i in range(1, n + 1):
        h[fa[i]].append(i)

    # 设根结点1深度为0
    def get_depth(t):
        nonlocal deepest
        q = deque([t])
        while q:
            u = q.popleft()
            for v in h[u]:
                depth[v] = depth[u] + 1  # 树中父亲唯一
                deepest = max(deepest, depth[v])
                q.append(v)

    get_depth(1)  # 预处理
    max1 = [[0] * 2 for _ in range(deepest + 1)]  # 每层选法最大值及其选择的点
    max2 = [[0] * 2 for _ in range(deepest + 1)]  # 每层选法次大值及其选择的点
    max3 = [0] * (deepest + 1)  # 每层不选的话，其选法最大值
    layer = [[] for _ in range(deepest + 1)]  # 求各层点
    for i in range(1, n + 1):
        layer[depth[i]].append(i)

    # 初始化
    f[1][0] = 0
    f[1][1] = w[1]
    max1[0] = [w[1], 1]
    # 按层遍历
    for i in range(1, deepest + 1):
        for j in layer[i]:
            # 不选j，直接从上一层的最大值转移而来，上一层选不选都行——因此二者取max
            f[j][0] = max(max1[i - 1][0], max3[i - 1])
            # 选j
            if (
                fa[j] != max1[i - 1][1]
            ):  # j的父亲是最大值。此时要么选上一层次大值，要么上一层不选——二者取max
                f[j][1] = max(max1[i - 1][0], max3[i - 1]) + w[j]
            else:
                f[j][1] = max(max2[i - 1][0], max3[i - 1]) + w[j]

            # 更新这一层选中点的最大值/次大值
            # 由于是选中，只需要考虑f[p][1]
            if f[j][1] > max1[i][0]:
                max2[i] = max1[i]
                max1[i] = [f[j][1], j]
            elif f[j][1] > max2[i][0]:
                max2[i] = [f[j][1], j]
            # 更新本层不选的最大值
            max3[i] = max(max3[i], f[j][0])

    # 寻找答案
    res = 0
    for p in layer[deepest]:
        res = max(res, max(f[p][0], f[p][1]))

    print(res)


if __name__ == "__main__":
    solve()
