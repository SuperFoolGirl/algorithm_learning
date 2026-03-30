import sys

sys.setrecursionlimit(200000)


def solve():
    data = sys.stdin.read().split()
    it = iter(data)
    ri = lambda: int(next(it))

    n, m = ri(), ri()
    res, cnt = 0, 0
    e = []
    p = list(range(n + 1))

    def find(x):
        if p[x] != x:
            p[x] = find(p[x])
        return p[x]

    def union(a, b):
        pa, pb = find(a), find(b)
        if pa != pb:
            p[pa] = pb
            return True
        return False

    def kruskal():
        e.sort()
        # 需要修改外层函数的变量，必须声明为nonlocal
        nonlocal res, cnt

        for w, a, b in e:
            if union(a, b):
                res += w
                cnt += 1
                if cnt == n - 1:
                    break

    for _ in range(m):
        u, v, w = ri(), ri(), ri()
        # 列表元素若为元组，排序默认按元组的第一个元素排序
        e.append((w, u, v))

    kruskal()

    if cnt < n - 1:
        print("IMPOSSIBLE")
    else:
        print(res)

if __name__ == "__main__":
    solve()
