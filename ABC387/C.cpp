#include <iostream>
#include <vector>

int main()
{
    int64_t L, R;
    std::cin >> L >> R;
    std::vector<int> digL(18, 0);
    std::vector<int> digR(18, 0);
    for (int i = 1; i <= 18; ++i)
    {
        digL[18 - i] = L % 10;
        L /= 10;
    }
    for (int i = 1; i <= 18; ++i)
    {
        digR[18 - i] = R % 10;
        R /= 10;
    }
    auto calc = [&](std::vector<int> &dig) -> int64_t
    {
        int firstIdx = 0;
        for (int i = 0; i < 18; ++i)
        {
            if (dig[i] != 0)
            {
                firstIdx = i;
                break;
            }
        }
        if (firstIdx == 16)
        {
            return dig[16];
        }
    };
    return 0;
}