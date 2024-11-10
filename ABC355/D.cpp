#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    struct RANGE
    {
        size_t begin;
        size_t end;
    };
    size_t N;
    std::cin >> N;
    std::vector<RANGE> ranges(N);
    RANGE tmp;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> tmp.begin >> tmp.end;
        ranges[i] = tmp;
    }
    std::sort(ranges.begin(), ranges.end(), [](const RANGE &lhs, const RANGE &rhs)
              { return lhs.begin < rhs.begin; });

    return 0;
}