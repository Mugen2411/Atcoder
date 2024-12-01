#include <iostream>
#include <list>
#include <vector>

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
    int64_t N, M;
    std::cin >> N >> M;
    std::vector<std::pair<int64_t, int64_t>> A;
    int64_t minA = 2e9;
    for (int i = 0; i < N; ++i)
    {
        int64_t a;
        std::cin >> a;
        if (a < minA)
        {
            minA = a;
            A.push_back({a, i + 1});
        }
    }

    while (M--)
    {
        int64_t B;
        std::cin >> B;

        int64_t idx = BinarySearch(-1, A.size(), [&](int64_t mid)
                                   { return A[mid].first <= B; });

        if (idx >= A.size())
        {
            std::cout << -1 << std::endl;
        }
        else
        {
            std::cout << A[idx].second << std::endl;
        }
    }
    return 0;
}