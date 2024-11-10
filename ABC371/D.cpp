#include <iostream>
#include <vector>
#include <algorithm>

template <class F>
int64_t BinarySearch(int64_t ng, int64_t ok, F comp)
{
    int64_t mid;
    while (std::abs(ng - ok) > 1)
    {
        mid = (ng + ok) / 2;
        if (comp(mid))
        {
            ok = mid;
        }
        else
        {
            ng = mid;
        }
    }
    return ok;
}

int main()
{
    size_t N;
    std::cin >> N;
    std::vector<int64_t> X(N + 1, 0);
    std::vector<int64_t> P(N + 1, 0);

    for (int i = 1; i <= N; ++i)
    {
        std::cin >> X[i];
    }

    for (int i = 0; i < N; ++i)
    {
        std::cin >> P[i + 1];
        P[i + 1] += P[i];
    }

    int64_t Q;
    std::cin >> Q;
    while (Q--)
    {
        int64_t L, R;
        std::cin >> L >> R;

        int64_t Lidx = BinarySearch(X.size(), 0, [&](int64_t mid)
                                    { return X[mid] < L; });
        int64_t Ridx = BinarySearch(X.size(), 0, [&](int64_t mid)
                                    { return X[mid] <= R; });

        std::cout << P[Ridx] - P[Lidx] << std::endl;
    }
}