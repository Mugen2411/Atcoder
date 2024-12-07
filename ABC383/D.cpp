#include <iostream>
#include <unordered_map>
#include <cmath>

int main()
{
    int64_t N;
    std::cin >> N;
    std::unordered_map<int64_t, int64_t> map;

    auto dfs = [&](auto self, int64_t cur) -> int64_t
    {
        if (map.count(cur) != 0)
        {
            return map[cur];
        }

        int64_t rt = std::sqrt(cur);
        int64_t ans = 0;

        for (int64_t i = 1; i <= rt; ++i)
        {
            if (cur % i == 0)
            {
                ans += self(cur / i) + self(i);
            }
        }
    };
    return 0;
}