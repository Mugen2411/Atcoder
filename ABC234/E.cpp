#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int64_t X;
    std::cin >> X;

    std::vector<int> vecX;
    int64_t x = X;
    while (x)
    {
        vecX.push_back(x % 10);
        x /= 10;
    }

    int64_t len = vecX.size();

    std::reverse(vecX.begin(), vecX.end());

    int64_t min = 1;
    for (int i = 1; i < len; ++i)
    {
        min *= 10;
    }
    std::vector<int64_t> candidates;

    for (int i = -9; i <= 9; ++i)
    {
        for (int j = 0; j <= 9; ++j)
        {
            if (j + i * (len - 1) > 9 || j + i * (len - 1) < 0)
            {
                continue;
            }
            int64_t tmp = 0;
            for (int k = 0; k < len; ++k)
            {
                tmp *= 10;
                tmp += j + i * k;
            }

            if (tmp < min)
            {
                continue;
            }
            candidates.push_back(tmp);
        }
    }

    std::sort(candidates.begin(), candidates.end());

    for (size_t ansIdx = 0; ansIdx < candidates.size(); ++ansIdx)
    {
        if (candidates[ansIdx] >= X)
        {
            std::cout << candidates[ansIdx];
            return 0;
        }
    }
    return 0;
}