import sys

sys.setrecursionlimit(200000)


def solve():
    data = sys.stdin.read().split()
    it = iter(data)
    ri = lambda: int(next(it))

    n, m = ri(), ri()
    # 创建三元组，但这样写效率要高于tuple([ri(), ri(), ri()])
    e = [(ri(), ri(), ri()) for _ in range(m)]
    p = list(range(n + 1))

    def find(x):
        if p[x] != x:
            p[x] = find(p[x])
        return p[x]

    def kruskal():
        e.sort(key=lambda x: x[2])
        res = 0

        for u, v, w in e:
            pu, pv = find(u), find(v)
            if (pu != pv):
                p[pu] = pv
            else:
                res += w
        return res
    
    sys.stdout.write(f"{kruskal()}\n")


if __name__ == "__main__":
    solve()
