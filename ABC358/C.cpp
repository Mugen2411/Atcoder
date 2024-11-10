#include <iostream>
#include <string>
#include <bit>

int main()
{
    size_t N, M;
    std::string S[10];
    std::cin >> N >> M;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> S[i];
    }
    size_t bit[10];
    for (int i = 0; i < N; ++i)
    {
        size_t b = 0;
        for (int j = 0; j < M; ++j)
        {
            b |= (S[i][j] == 'o') << j;
        }
        bit[i] = b;
    }
    int ans = 99999;
    for (int i = 0; i < 1 << N; ++i)
    {
        size_t tmp = 0;
        for (int j = 0; j < N; ++j)
        {
            if (i & 1 << j)
            {
                tmp |= bit[j];
            }
        }
        if (tmp != (1 << M) - 1)
        {
            continue;
        }
        ans = std::min(ans, std::__popcount(i));
    }
    std::cout << ans;
    return 0;
}