def BinarySearch(ng, ok, comp):
    mid = ok
    while abs(ng - ok) > 1:
        mid = (ng + ok) // 2
        if comp(mid):
            ok = mid
        else:
          ng = mid
    return ok

T = int(input())
for t in range(T):
    Ns = input()
    N = int(Ns)

    def fn(cur):
        return cur * cur >= N

    a = BinarySearch(0, N + 1, fn)

    mx = a * a
    diff = mx - N

    all = (a - 1) * a * 2
    all -= (diff // a) * (a * 2 - 1)
    all -= (diff % a) * 2

    print(all)