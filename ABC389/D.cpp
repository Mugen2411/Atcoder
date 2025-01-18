#include <iostream>
#include <vector>
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

int main()
{
    int64_t R;
    std::cin >> R;
    int64_t ans = 0;
    for (int i = 1; i <= R; ++i)
    {
        int64_t idx = BinarySearch(R + 1, 0, [&](int64_t cur)
                                   {
            bool isRU = (i-0.5)*(i-0.5) + (cur + 0.5) * (cur + 0.5) <= (R * R);
            bool isRD = (i+0.5)*(i+0.5) + (cur + 0.5) * (cur + 0.5) <= (R * R);
            return isRD & isRU ; });
        ans += idx;
    }
    std::cout << ans * 4 + (R * 4) - 3;
    return 0;
}