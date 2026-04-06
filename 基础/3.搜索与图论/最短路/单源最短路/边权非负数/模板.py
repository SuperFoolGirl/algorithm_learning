import sys
import heapq  # python只有小根堆


def solve():
    it = iter(sys.stdin.read().split())
    ri = lambda: int(next(it))

    n, m = ri(), ri()
    # h[a]存储若干个二元组(b,c)，表示a->b的边权为c
    h = [[] for _ in range(n + 1)]

    def dijkstra(start):
        # dist列表的元素是基础类型，即不可变对象，直接浅拷贝即可
        # 换句话说，就是可以统一赋值
        # float("inf")表示正无穷，float("-inf")表示负无穷
        # 创建一个含有n+1个元素为无穷大的列表
        dist = [float("inf")] * (n + 1)
        dist[start] = 0

        # 定义heap列表作为堆，它只是列表
        # 注意，必须让距离作为堆元素的第一个值，因为这是默认排序字段
        heap = [(0, start)]

        while heap:
            d, u = heapq.heappop(heap)

            if u == n:
                break
            if d > dist[u]:
                continue

            for v, w in h[u]:
                if dist[v] > d + w:
                    dist[v] = d + w
                    heapq.heappush(heap, (dist[v], v))
        return dist[n]

    for _ in range(m):
        a, b, c = ri(), ri(), ri()
        # h[i]->[(a,b),(c,d),...]
        h[a].append((b, c))  # 干掉了add

    res = dijkstra(1)
    # 三元表达式
    print(res if res != float("inf") else -1)


if __name__ == "__main__":
    solve()
