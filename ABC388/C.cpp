#include <iostream>
#include <vector>

#ifndef ___INCLUDED_BINARY_SEARCH___
#define ___INCLUDED_BINARY_SEARCH___

#include <cstdint>

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

#endif //___INCLUDED_BINARY_SEARCH___

int main()
{
    size_t N;
    std::cin >> N;
    std::vector<int64_t> A(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> A[i];
    }
    int64_t ans = 0;
    for (int i = 0; i < N; ++i)
    {
        int64_t idx = BinarySearch(N, -1, [&](int64_t idx)
                                   { return A[idx] <= A[i] / 2; });
        if (idx != -1 && idx != N)
        {
            ans += idx + 1;
        }
    }
    std::cout << ans;
    return 0;
}