import sys

sys.setrecursionlimit(200000)


def solve():
    data = sys.stdin.read().split()
    it = iter(data)
    ri = lambda: int(next(it))
    rs = lambda: next(it)

    k = ri()
    g = []
    st = []
    xa, ya, xb, yb = 0, 0, 0, 0
    n = 0
    dx = [-1, 0, 1, 0]
    dy = [0, 1, 0, -1]

    def dfs(x, y):
        if g[x][y] == '#':
            return False
        if (x, y) == (xb, yb):
            return True
        
        st[x][y] = True
        for i in range(4):
            a, b = x + dx[i], y + dy[i]
            if a < 0 or a >= n or b < 0 or b >= n:
                continue
            if g[a][b] == '#' or st[a][b]:
                continue
            if dfs(a, b):
                return True
        return False

    while k:
        k -= 1
        n = ri()
        g = [rs() for _ in range(n)]
        st = [[False] * n for _ in range(n)]
        xa, ya, xb, yb = ri(), ri(), ri(), ri()

        if dfs(xa, ya):
            sys.stdout.write("YES\n")
        else:
            sys.stdout.write("NO\n")


if __name__ == "__main__":
    solve()
