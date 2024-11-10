#include <iostream>
#include <vector>

int main()
{
    size_t N;
    std::cin >> N;
    std::vector<int64_t> K(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> K[i];
    }

    int64_t diff = 9999999999999;
    int64_t ans;
    for (int64_t i = 0; i < 1 << N; ++i)
    {
        int64_t sumA = 0, sumB = 0;
        for (int j = 0; j < N; ++j)
        {
            if (i & (1 << j))
            {
                sumA += K[j];
            }
            else
            {
                sumB += K[j];
            }
        }
        if (diff > std::abs(sumA - sumB))
        {
            diff = std::abs(sumA - sumB);
            ans = std::max(sumA, sumB);
        }
    }
    std::cout << ans;
    return 0;
}