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
        std::cout << -1;
        return 0;
    }

    int64_t ans = 0;
    for (int i = 0; i < M - 1; ++i)
    {
        int64_t dist = xa[i + 1].X - xa[i].X;
        if (xa[i].A >= dist)
        {
            ans += (xa[i].A - 1 + xa[i].A - dist) * dist / 2;
            xa[i + 1].A += xa[i].A - dist;
            xa[i].A = dist;
        }
        else
        {
            std::cout << -1;
            return 0;
        }
    }
    if (xa[M - 1].A != N - xa[M - 1].X + 1)
    {
        std::cout << -1;
        return 0;
    }
    ans += (xa[M - 1].A - 1) * xa[M - 1].A / 2;

    std::cout << ans;

    return 0;
}