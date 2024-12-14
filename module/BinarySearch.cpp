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