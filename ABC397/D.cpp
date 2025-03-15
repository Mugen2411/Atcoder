#ifndef ___INCLUDED_BINARY_SEARCH___
#define ___INCLUDED_BINARY_SEARCH___

#include <cstdint>
#include <cmath>

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

#include <iostream>

int main()
{
    int64_t N;
    std::cin >> N;
    int64_t cN = std::cbrtl(N);
    int64_t rN = std::sqrt(N);

    for (int64_t diff = 1; diff <= cN; ++diff)
    {
        if (N % diff != 0)
        {
            continue;
        }

        int64_t a = N / diff;

        int64_t ansY = BinarySearch(0, rN, [&](int64_t cur)
                                    {
            int64_t x = cur + diff;
            int64_t y = cur;
            
            return a <= (x * x + x * y + y * y); });

        int64_t ansX = ansY + diff;
        if (ansX * ansX * ansX - ansY * ansY * ansY == N)
        {
            std::cout << ansX << " " << ansY;
            return 0;
        }
    }
    std::cout << "-1";
    return 0;
}