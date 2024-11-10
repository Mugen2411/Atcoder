#include <iostream>
#include <array>
#include <vector>

int main()
{
    size_t N, S;
    std::cin >> N >> S;

    std::array<int, 10> d({0});
    while (S)
    {
        ++d[S % 10];
        S /= 10;
    }

    std::vector<std::array<int, 10>> ansList;

    int64_t limit = 1;
    for (int i = 0; i < N; ++i)
    {
        limit *= 10;
    }

    for (int64_t i = 0; i * i < limit; ++i)
    {
        ansList.push_back(std::array<int, 10>({0}));
        int64_t t = i * i;
        while (t)
        {
            ++ansList.back()[t % 10];
            t /= 10;
        }
    }

    size_t ans = 0;
    for (auto &i : ansList)
    {
        bool isSame = true;
        for (int j = 1; j < 10; ++j)
        {
            if (d[j] != i[j])
            {
                isSame = false;
                break;
            }
        }

        if (isSame)
        {
            ++ans;
        }
    }

    std::cout << ans;
    return 0;
}