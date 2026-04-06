import sys
from itertools import islice

sys.setrecursionlimit(200000)


def solve():
    it = iter(sys.stdin.read().split())
    ri = lambda: int(next(it))
    rs = lambda: next(it)

    # [] <=> list()
    # [0] + [ri() for _ in range(k)]  -> 一维数组 + 一维数组
    # [0] * n -> [0,0,...,0]
    # [0 for _ in range(n)] -> [0,0,...,0]
    # [[0] for _ in range(n)] -> [[0],[0],...,[0]]

    # 读入单个变量
    n, m = ri(), ri()

    # 读入字符串
    s = rs()

    # 读入一维int数组
    a1 = list(map(int, islice(it, n)))

    # 读入一维char数组
    a2 = list(islice(it, n))

    # 读入二维int数组
    g1 = [list(map(int, islice(it, m))) for _ in range(n)]

    # 读入二维char数组
    g2 = [list(islice(it, m)) for _ in range(n)]

    # 读入无空格的二维char数组
    g3 = [list(rs()) for _ in range(n)]

    # 读入二元组数组(坐标)
    # islice(it, 2 * n)：取出前2*n个迭代器
    # map(int, islice(...)) -> map_obj
    # (map_obj,) * 2 -> (map_obj, map_obj)
    # zip(*(map_obj, map_obj)) -> 解包，相当于zip(map_obj, map_obj)，得到一个迭代器，元素为二元组
    # 总结：list(zip(*(map_obj,) * 2))
    p = list(zip(*(map(int, islice(it, 2 * n)),) * 2))

    # 读入三元组数组(边，用于kruskal)
    e1 = list(zip(*(map(int, islice(it, 3 * m)),) * 3))

    # 变长数据(n行元素，每行k个元素)
    data = []
    for _ in range(n):
        k = ri()
        data.append(list(islice(it, k)))

    # 读入邻接表(无向边)
    g4 = [[] for _ in range(n + 1)]
    e2 = zip(*(map(int, islice(it, 3 * m)),) * 3)  # 只遍历就不需要list
    for u, v, w in e2:
        g4[u].append((v, w))
        g4[v].append((u, w))

    # 读到EOF
    try:
        while True:
            # 读入
            x = ri()
    except StopIteration:
        pass

    # 读到0为止
    while True:
        x = ri()
        if x == 0:
            break

    sys.stdout.write(f"\n")


if __name__ == "__main__":
    solve()
