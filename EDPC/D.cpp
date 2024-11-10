#include <iostream>

int64_t dp[110][110000] = {0};

int main()
{
    size_t N, W;
    std::cin >> N >> W;
    int64_t w[110] = {0};
    int64_t v[110] = {0};
    for (int i = 0; i < N; ++i)
    {
        std::cin >> w[i] >> v[i];
    }

    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= W; ++j)
        {
            dp[i][j] = std::max(dp[i][j], dp[i - 1][j]);
            if (j >= w[i - 1])
            {
                dp[i][j] = std::max(dp[i][j], dp[i - 1][j - w[i - 1]] + v[i - 1]);
            }
        }
    }
    std::cout << dp[N][W];
    return 0;
}