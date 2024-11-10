#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    int64_t N, M;
    std::cin >> N >> M;

    std::vector<int64_t> X(M);
    std::vector<int64_t> A(M);

    struct XA
    {
        int64_t X;
        int64_t A;
    };

    std::vector<XA> xa(M);

    for (int i = 0; i < M; ++i)
    {
        std::cin >> X[i];
    }
    for (int i = 0; i < M; ++i)
    {
        std::cin >> A[i];
    }
    for (int i = 0; i < M; ++i)
    {
        xa[i].X = X[i];
        xa[i].A = A[i];
    }
    std::sort(xa.begin(), xa.end(), [](const XA &lhs, const XA &rhs)
              { return lhs.X < rhs.X; });

    if (xa[0].X != 1)
    {
        std::cout << -1 << std::endl;
        return 0;
    }

    int64_t sum = 0;
    for (auto &i : xa)
    {
        sum += i.A;
    }
    if (sum != N)
    {
        std::cout << -1 << std::endl;
        return 0;
    }

    int64_t ans = 0;

    auto f = [&](auto self, int i) -> int64_t
    {
        if (i == M - 1)
        {
            ans += xa[i].A * (xa[i].A - 1) / 2;
            return xa[i].A;
        }

        int64_t dist = xa[i + 1].X - xa[i].X;
        int64_t a = xa[i].A - dist;
        int64_t begin = xa[i].A - 1;
        int64_t last = xa[i].A - dist;

        ans += (begin + last) * dist / 2;

        int64_t deltaTime = self(self, i + 1);

        ans += a * (deltaTime - 1);
        ans += a * (a + 1) / 2;

        return deltaTime + a + dist;
    };

    int64_t allTime = f(f, 0);
    if (allTime != N)
    {
        std::cout << -1 << std::endl;
        return 0;
    }

    std::cout << ans << std::endl;

    return 0;
}