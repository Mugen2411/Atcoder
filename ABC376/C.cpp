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
    std::vector<int64_t> A(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> A[i];
    }
    std::sort(A.begin(), A.end(), std::greater<int64_t>());

    std::vector<int64_t> B(N);
    for (int i = 0; i < N - 1; ++i)
    {
        std::cin >> B[i];
    }
    std::sort(B.begin(), B.end(), std::greater<int64_t>());

    int64_t ans = BinarySearch(-10, 2000000000, [&](int64_t mid)
                               {
        std::vector<int64_t> tmp(B);
        int64_t add = mid;
        int64_t curB = 0;
        for(int i=0; i<N; ++i)
        {
            if(A[i] <= B[curB])
            {
                ++curB;
                continue;
            }else
            {
                if(A[i] <= add)
                {
                    add = -10;
                    continue;
                }else
                {
                    return false;
                }
            }
        }
        return true; });

    if (ans >= 1500000000)
    {
        std::cout << -1;
    }
    else
    {
        std::cout << ans;
    }
    return 0;
}